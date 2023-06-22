using Android.App;
using Android.Content.PM;
using Android.Graphics;
using Android.OS;

namespace MieleSmartWaterTap.Droid
{
    [Activity(Label = "MieleSmartWaterTapMain", Theme = "@style/MainTheme",
        ConfigurationChanges = ConfigChanges.ScreenSize | ConfigChanges.Orientation)]
    public class MainActivity : global::Xamarin.Forms.Platform.Android.FormsAppCompatActivity
    {
        protected override void OnCreate(Bundle savedInstanceState)
        {
            TabLayoutResource = Resource.Layout.Tabbar;
            ToolbarResource = Resource.Layout.Toolbar;
            RequestedOrientation = ScreenOrientation.Landscape;

            base.OnCreate(savedInstanceState);
            Window.SetStatusBarColor(Color.ParseColor("#3b3c3e"));

            Xamarin.Forms.Forms.Init(this, savedInstanceState);
            var container = UnityContainerBuilder.Instance;

            var formsApp = new App(container);
            formsApp.InitializeFormsApplication(container);

            LoadApplication(formsApp);
        }
    }
}