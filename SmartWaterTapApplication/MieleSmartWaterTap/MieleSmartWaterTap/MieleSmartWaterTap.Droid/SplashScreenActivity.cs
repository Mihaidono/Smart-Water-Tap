using System;
using System.Threading.Tasks;
using Android.App;
using Android.Content;
using Android.Content.PM;

namespace MieleSmartWaterTap.Droid
{
    [Activity(Label = "MieleSmartWaterTap", Theme = "@style/SplashScreenTheme", Icon = "@drawable/appIcon",
        MainLauncher = true, NoHistory = true,
        ConfigurationChanges = ConfigChanges.ScreenSize | ConfigChanges.Orientation)]
    public class SplashScreenActivity : global::Xamarin.Forms.Platform.Android.FormsAppCompatActivity
    {
        // Launches the startup task
        protected override void OnResume()
        {
            base.OnResume();
            RequestedOrientation = ScreenOrientation.Landscape;
            var startupWork = new Task(SimulateStartup);
            
            startupWork.Start();
        }

        // Simulates background work that happens behind the splash screen
        private async void SimulateStartup()
        {
            await Task.Delay(2000); // Simulate a bit of startup work.
            StartActivity(new Intent(Application.Context, typeof(MainActivity)));
        }
    }
}