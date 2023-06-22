using System.Threading.Tasks;
using MieleSmartWaterTap.Models.DTOs;
using Refit;

namespace MieleSmartWaterTap.Services
{
    public interface IHttpService
    {
        Task RotateWaterTap([Body(BodySerializationMethod.Serialized)] SmartWaterTapDto state);
        Task<SmartWaterTapDto> GetWaterTapName();
        Task<SmartWaterTapDto> GetWaterTapState();
        void SetClientHostUrl(string ip);
    }
}