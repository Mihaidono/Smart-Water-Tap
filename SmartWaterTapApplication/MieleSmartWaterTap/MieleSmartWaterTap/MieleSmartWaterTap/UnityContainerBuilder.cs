using System;
using MieleSmartWaterTap.Services;
using MieleSmartWaterTap.Services.Implementations;
using Unity;

namespace MieleSmartWaterTap
{
    public class UnityContainerBuilder
    {
        #region Fields and Properties

        private static readonly Lazy<UnityContainerBuilder> _lazy = new(() => new UnityContainerBuilder());

        public static UnityContainerBuilder Instance => _lazy.Value;

        private readonly IUnityContainer _container;

        #endregion

        #region Constructor

        private UnityContainerBuilder()
        {
            _container = new UnityContainer();

            RegisterDependencies();
        }

        #endregion

        #region Methods

        private void RegisterDependencies()
        {
            _container.RegisterSingleton<IHttpService, HttpService>();
            _container.RegisterSingleton<IPingTapsIpService, PingTapsIpService>();
        }

        #endregion

        #region Wrappers

        public void RegisterSingleton<TAbstraction, TImpl>()
        {
            _container.RegisterSingleton(typeof(TAbstraction), typeof(TImpl));
        }

        public T Resolve<T>()
        {
            return _container.Resolve<T>();
        }

        public object Resolve(Type type)
        {
            return _container.Resolve(type);
        }

        #endregion
    }
}