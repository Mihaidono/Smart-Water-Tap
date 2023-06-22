using System.Collections.Generic;
using System.Net.NetworkInformation;
using System.Threading.Tasks;
using MieleSmartWaterTap.Models;

namespace MieleSmartWaterTap.Services;

public interface IPingTapsIpService
{
    Task<List<SmartWaterTap>> GetConnectedDevicesAsync();
    Task<List<string>> GetAvailableIpAddressesAsync();
    Task<PingReply> PingAsync(string ipAddress);
}