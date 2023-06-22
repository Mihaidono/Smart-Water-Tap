using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Input;
using MieleSmartWaterTap.Models;
using MieleSmartWaterTap.Services;
using MieleSmartWaterTap.Views;
using Xamarin.Forms;

namespace MieleSmartWaterTap.ViewModels;

[QueryProperty("LastTapNameAccessed", "UpdatedTapName")]
[QueryProperty("LastTapStateAccessed", "UpdatedTapState")]
public class MainPageViewModel : BaseViewModel
{
    #region Fields and Properties

    private string _lastTapNameAccessed;
    public string LastTapNameAccessed
    {
        get => _lastTapNameAccessed;
        set => SetProperty(ref _lastTapNameAccessed, value);
    }

    private string _lastTapStateAccessed;
    public string LastTapStateAccessed
    {
        get => _lastTapStateAccessed;
        set
        {
            SetProperty(ref _lastTapStateAccessed, value);
            UpdateSmartWaterTapsList();
        }
    }

    private ObservableCollection<SmartWaterTap> _smartWaterTaps;
    public ObservableCollection<SmartWaterTap> SmartWaterTaps
    {
        get => _smartWaterTaps;
        set => SetProperty(ref _smartWaterTaps, value);
    }

    private bool _isRefreshing;
    public bool IsRefreshing
    {
        get => _isRefreshing;
        set => SetProperty(ref _isRefreshing, value);
    }

    private readonly IPingTapsIpService _pingTapsIpService;

    #endregion

    #region Constructor

    public MainPageViewModel(IPingTapsIpService pingTapsIpService)
    {
        _pingTapsIpService = pingTapsIpService ?? throw new ArgumentNullException(nameof(pingTapsIpService));

        SmartWaterTaps = new ObservableCollection<SmartWaterTap>();

        GoToSmartWaterTapDetailPage =
            new Command<SmartWaterTap>(async (tap) => await GoToSmartWaterTapDetailPageAsync(tap));

        RefreshCommand = new Command(async () => await RefreshAsync());
    }

    #endregion

    #region Commands

    public ICommand RefreshCommand { get; }
    public ICommand GoToSmartWaterTapDetailPage { get; }

    #endregion

    #region Command Methods

    private async Task RefreshAsync()
    {
        SmartWaterTaps = new ObservableCollection<SmartWaterTap>(await _pingTapsIpService.GetConnectedDevicesAsync());
        IsRefreshing = false;
    }

    private static async Task GoToSmartWaterTapDetailPageAsync(SmartWaterTap tap)
    {
        Routing.RegisterRoute(nameof(SmartWaterTapDetailPage), typeof(SmartWaterTapDetailPage));
        await Shell.Current.GoToAsync(
            $"SmartWaterTapDetailPage?Name={tap.Name}&State={tap.State}&IpAddress={tap.IpAddress}&DeviceType={tap.DeviceType}");
    }

    #endregion

    #region Methods

    private void UpdateSmartWaterTapsList()
    {
        var updatedTap = SmartWaterTaps.FirstOrDefault(tap => tap.Name == LastTapNameAccessed);
        if (updatedTap == null) return;
        updatedTap.State = LastTapStateAccessed;
        var indexOfUpdatedTap = SmartWaterTaps.IndexOf(updatedTap);
        SmartWaterTaps[indexOfUpdatedTap] = updatedTap;
    }

    #endregion
}