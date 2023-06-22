using MieleSmartWaterTap.Views;
using Xamarin.Forms;
using Xamarin.Forms.Xaml;

namespace MieleSmartWaterTap
{
    [XamlCompilation(XamlCompilationOptions.Compile)]
    public partial class AppShell : Shell
    {
        public AppShell()
        {
            InitializeComponent();
        }
    }
}