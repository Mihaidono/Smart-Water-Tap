using System;
using System.Globalization;
using Xamarin.Forms;

namespace MieleSmartWaterTap.Converters
{
    public class ViewModelConverter : IValueConverter
    {
        public object Convert(object value,
                              Type targetType,
                              object parameter,
                              CultureInfo culture)
        {
            var container = value as UnityContainerBuilder;
            var viewModelType = parameter as Type;

            var viewModel = container.Resolve(viewModelType);

            return viewModel;
        }

        public object ConvertBack(object value,
                                  Type targetType,
                                  object parameter,
                                  CultureInfo culture)
        {
            throw new NotSupportedException();
        }
    }
}