using System.Text.Json.Serialization;

namespace MieleSmartWaterTap.Models.DTOs;

public class SmartWaterTapDto
{
    [JsonPropertyName("device-name")]
    public string DeviceName { get; set; }

    [JsonPropertyName("state")] 
    public string State { get; set; }
    
    [JsonPropertyName("device-type")]
    public string DeviceType { get; set; }
}