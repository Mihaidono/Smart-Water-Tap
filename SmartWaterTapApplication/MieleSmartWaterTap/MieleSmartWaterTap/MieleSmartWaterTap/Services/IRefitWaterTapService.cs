using System;
using System.Threading.Tasks;
using MieleSmartWaterTap.Models.DTOs;
using Refit;

namespace MieleSmartWaterTap.Services;

public interface IRefitWaterTapService : IDisposable
{
    [Post("/rotate")]
    Task RotateWaterTap([Body(BodySerializationMethod.Serialized)] SmartWaterTapDto state);

    [Get("/")]
    Task<SmartWaterTapDto> GetWaterTapName();

    [Get("/state")]
    Task<SmartWaterTapDto> GetWaterTapState();
}