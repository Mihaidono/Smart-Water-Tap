using System;
using Unity;
using Xamarin.Forms;
using Xamarin.Forms.Xaml;

[assembly: XamlCompilation(XamlCompilationOptions.Compile)]

namespace MieleSmartWaterTap
{
    public partial class App : Application
    {
        public App(UnityContainerBuilder? unityContainerBuilder)
        {
            _ = unityContainerBuilder ?? throw new ArgumentNullException(nameof(unityContainerBuilder));
			
            InitializeComponent();
			
            var appShell = unityContainerBuilder.Resolve<AppShell>();

            Current.MainPage = appShell;
        }
		
        public void InitializeFormsApplication(UnityContainerBuilder unityContainerBuilder)
        {
            _ = unityContainerBuilder ?? throw new ArgumentNullException(nameof(unityContainerBuilder));
            
            Resources[nameof(IUnityContainer)] = unityContainerBuilder;
        }
    }
}