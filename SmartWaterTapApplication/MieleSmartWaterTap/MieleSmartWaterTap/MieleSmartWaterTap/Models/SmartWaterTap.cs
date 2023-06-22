using MieleSmartWaterTap.Models.DTOs;

namespace MieleSmartWaterTap.Models;

public class SmartWaterTap
{
    #region Fields and Properties

    public string Name { get; set; }
    public string State { get; set; }
    public string DeviceType { get; set; }
    public string IpAddress { get; set; }

    #endregion

    #region Constructors

    public SmartWaterTap(string ipAddress, SmartWaterTapDto waterTapDto)
    {
        IpAddress = ipAddress;
        Name = waterTapDto.DeviceName;
        State = waterTapDto.State;
        DeviceType = waterTapDto.DeviceType;
    }
    
    public SmartWaterTap(string ipAddress, string deviceName,string deviceState, string deviceType)
    {
        IpAddress = ipAddress;
        Name = deviceName;
        State = deviceState;
        DeviceType = deviceType;
    }

    #endregion
}