using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Net.NetworkInformation;
using System.Text.Json;
using System.Threading.Tasks;
using MieleSmartWaterTap.Models;
using MieleSmartWaterTap.Models.DTOs;

namespace MieleSmartWaterTap.Services.Implementations;

public class PingTapsIpService : IPingTapsIpService
{
    public async Task<List<SmartWaterTap>> GetConnectedDevicesAsync()
    {
        var ipAddresses = await GetAvailableIpAddressesAsync();

        var connectedTaps = new List<SmartWaterTap>();
        var tasks = ipAddresses.Select(QuestionEndpoint).ToList();
        var results = await Task.WhenAll(tasks);

        foreach (var result in results)
        {
            try
            {
                var bareObject = await result.Value.Content.ReadAsStringAsync();
                var finalObject = JsonSerializer.Deserialize<SmartWaterTapDto>(bareObject);

                if (ValidateDeviceResponse(finalObject))
                {
                    connectedTaps.Add(new SmartWaterTap(result.Key, finalObject));
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.Message);
            }
        }

        return connectedTaps;
    }

    public async Task<List<string>> GetAvailableIpAddressesAsync()
    {
        var tasks = new List<Task<PingReply>>();
        var baseIpAddress = GetIpAddressPrefix(GetLocalIpAddress());
        for (var i = 2; i <= 255; i++)
        {
            var ipAddress = $"{baseIpAddress}.{i}";
            tasks.Add(PingAsync(ipAddress));
        }
        var results = await Task.WhenAll(tasks);
        return (from t in results where t.Status == IPStatus.Success select t.Address.ToString()).ToList();
    }

    public async Task<PingReply> PingAsync(string ipAddress)
    {
        using var ping = new Ping();
        return await ping.SendPingAsync(ipAddress, 1000);
    }

    private static async Task<KeyValuePair<string, HttpResponseMessage>> QuestionEndpoint(string ipAddress)
    {
        using var client = new HttpClient { Timeout = TimeSpan.FromMilliseconds(2000) };
        var response = new HttpResponseMessage();
        try
        {
            response = await client.GetAsync(new Uri($"http://{ipAddress}/state"));
        }
        catch (Exception ex)
        {
            Debug.WriteLine(ex.Message);
        }
        return new KeyValuePair<string, HttpResponseMessage>(ipAddress, response);
    }

    private static string GetLocalIpAddress()
    {
        var ipAddress = Dns.GetHostEntry(Dns.GetHostName())
                           .AddressList
                           .FirstOrDefault(ip => ip.AddressFamily == System.Net.Sockets.AddressFamily.InterNetwork);
        return ipAddress?.ToString() ?? "";
    }

    private static string GetIpAddressPrefix(string ipAddress)
    {
        var fields = ipAddress.Split('.');
        return fields[0] + "." + fields[1] + "." + fields[2];
    }

    private static bool ValidateDeviceResponse(SmartWaterTapDto response)
    {
        return response is { State: { }, DeviceName: { } };
    }
}