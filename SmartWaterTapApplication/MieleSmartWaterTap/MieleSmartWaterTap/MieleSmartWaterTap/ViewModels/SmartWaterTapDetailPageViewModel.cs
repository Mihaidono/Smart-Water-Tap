using System;
using System.Diagnostics;
using System.Net.Http;
using System.Threading.Tasks;
using System.Windows.Input;
using Lottie.Forms;
using MieleSmartWaterTap.Models.DTOs;
using MieleSmartWaterTap.Services;
using Xamarin.Forms;

namespace MieleSmartWaterTap.ViewModels;

[QueryProperty("DeviceType", "DeviceType")]
[QueryProperty("IpAddress", "IpAddress")]
[QueryProperty("TapName", "Name")]
[QueryProperty("TapState", "State")]
public class SmartWaterTapDetailPageViewModel : BaseViewModel
{
    #region Fields and Properties

    private string _deviceType;
    public string DeviceType
    {
        get => _deviceType;
        set => SetProperty(ref _deviceType, value);
    }

    private string _ipAddress;
    public string IpAddress
    {
        get => _ipAddress;
        set => SetProperty(ref _ipAddress, value);
    }

    private string _tapName;
    public string TapName
    {
        get => _tapName;
        set => SetProperty(ref _tapName, value);
    }

    private string _tapState;
    public string TapState
    {
        get => _tapState;
        set
        {
            SetProperty(ref _tapState, value);
            
            RotateButtonText = TapState == "open" ? "Close the Tap" : "Open the Tap";
            ChangeAnimationState(TapState == "close" ? "online" : "running");
        }
    }

    private bool _isRotateCommandAvailable = true;
    public bool IsRotateCommandAvailable
    {
        get => _isRotateCommandAvailable;
        set => SetProperty(ref _isRotateCommandAvailable, value);
    }

    private bool _canGoBack;
    public bool CanGoBack
    {
        get => _isRotateCommandAvailable;
        set => SetProperty(ref _canGoBack, value);
    }

    private string _rotateButtonText;
    public string RotateButtonText
    {
        get => _rotateButtonText;
        set => SetProperty(ref _rotateButtonText, value);
    }

    private string _currentLottiePlaying;
    public string CurrentLottiePlaying
    {
        get => _currentLottiePlaying;
        set => SetProperty(ref _currentLottiePlaying, value);
    }

    private readonly IHttpService _httpService;

    #endregion

    #region Constructor

    public SmartWaterTapDetailPageViewModel(IHttpService httpService)
    {
        _httpService = httpService ?? throw new ArgumentNullException(nameof(httpService));

        RotateTapCommand = new Command(async () => await RotateTapAsync());
        GoBackCommand = new Command(async () => await GoBackAsync());
    }

    #endregion

    #region Commands

    public ICommand RotateTapCommand { get; }
    public ICommand GoBackCommand { get; }

    #endregion

    #region Command Methods

    private async Task RotateTapAsync()
    {
        IsRotateCommandAvailable = false;
        var newState = TapState == "open" ? "close" : "open";
        try
        {
            _httpService.SetClientHostUrl(IpAddress);
            var currentSmartWaterTap = new SmartWaterTapDto
            {
                State = newState
            };
            ChangeAnimationState("off_to_on");
            await _httpService.RotateWaterTap(currentSmartWaterTap);
        }
        catch (HttpRequestException ex)
        {
            Debug.WriteLine(ex.Message);
        }
        finally
        {
            TapState = newState;
            IsRotateCommandAvailable = true;
        }
    }

    private async Task GoBackAsync()
    {
        await Shell.Current.GoToAsync($"..?UpdatedTapState={TapState}&UpdatedTapName={TapName}");
    }

    #endregion

    #region Methods

    private void ChangeAnimationState(string animationState)
    {
        var animationType = string.Empty;
        switch (DeviceType)
        {
            case "DISH_WASHER":
                animationType += "DishWasher";
                break;
            case "WASHING_MACHINE":
                animationType += "WashingMachine";
                break;
            case "DRYER":
                animationType += "Dryer";
                break;
            case "FRIDGE":
                animationType += "Refrigerator";
                break;
        }

        CurrentLottiePlaying = $"Resources.{animationType}Animations.{animationState}.json";
    }

    #endregion
}