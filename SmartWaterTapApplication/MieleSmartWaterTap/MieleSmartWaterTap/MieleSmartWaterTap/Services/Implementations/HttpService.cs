using System;
using System.Net.Http;
using System.Threading.Tasks;
using MieleSmartWaterTap.Models.DTOs;
using Refit;

namespace MieleSmartWaterTap.Services.Implementations
{
    public class HttpService : IHttpService
    {
        #region Fields and Properties

        private static IRefitWaterTapService _waterTapService;
        private string HostUrl { get; set; }

        #endregion

        #region Interface Implementation

        public async Task RotateWaterTap(SmartWaterTapDto state)
        {
            using (_waterTapService = RestService.For<IRefitWaterTapService>(
                       new HttpClient { BaseAddress = new Uri(HostUrl) },
                       new RefitSettings(new SystemTextJsonContentSerializer()) { Buffered = true }))
            {
                await _waterTapService.RotateWaterTap(state);
            }
        }

        public async Task<SmartWaterTapDto> GetWaterTapName()
        {
            using (_waterTapService = RestService.For<IRefitWaterTapService>(
                       new HttpClient { BaseAddress = new Uri(HostUrl) },
                       new RefitSettings(new SystemTextJsonContentSerializer())))
            {
                var response = await _waterTapService.GetWaterTapName();
                _ = response ?? throw new ArgumentNullException(nameof(response));
                return response;
            }
        }

        public async Task<SmartWaterTapDto> GetWaterTapState()
        {
            using (_waterTapService = RestService.For<IRefitWaterTapService>(
                       new HttpClient { BaseAddress = new Uri(HostUrl) },
                       new RefitSettings(new SystemTextJsonContentSerializer())))
            {
                var response = await _waterTapService.GetWaterTapState();
                _ = response ?? throw new ArgumentNullException(nameof(response));
                return response;
            }
        }

        #endregion

        public void SetClientHostUrl(string ip)
        {
            HostUrl = $"http://{ip}";
        }
    }
}