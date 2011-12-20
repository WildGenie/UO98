using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Linq;
using System.ServiceProcess;
using System.Text;
using System.Runtime.InteropServices;
using System.Threading;
using System.IO;
using System.Reflection;

namespace UO98
{
    partial class UO98Service : ServiceBase
    {
        public const string UniqueServiceName = "UO98";

        Thread workerThread = null;

        public UO98Service()
        {
            InitializeComponent();
            CanPauseAndContinue = false;
            ServiceName = UniqueServiceName;
            CanHandlePowerEvent = false;
            CanHandleSessionChangeEvent = false;
            CanStop = true;

            this.EventLog.Source = UniqueServiceName;
        }

        protected override void OnStart(string[] args)
        {
            IntPtr handle = this.ServiceHandle;
            myServiceStatus.currentState = (int)State.SERVICE_START_PENDING;
            SetServiceStatus(handle, myServiceStatus);

            if ((workerThread == null) ||
                ((workerThread.ThreadState &
                (System.Threading.ThreadState.Unstarted | System.Threading.ThreadState.Stopped)) != 0))
            {
                workerThread = new Thread(new ThreadStart(Program.Run));
                System.Diagnostics.Trace.WriteLine("Starting Service Worker Thread.");
                workerThread.Start();
            }
            if (workerThread != null)
            {
                EventLog.WriteEntry("OnStart - Worker thread state = " + workerThread.ThreadState.ToString());
            }

            myServiceStatus.currentState = (int)State.SERVICE_RUNNING;
            SetServiceStatus(handle, myServiceStatus);
            EventLog.WriteEntry("Started Service. Working directory: " + Directory.GetCurrentDirectory());

        }

        protected override void OnStop()
        {
            this.RequestAdditionalTime(4000);

            if ((workerThread != null) && (workerThread.IsAlive))
            {
                workerThread.Abort();
            }
            if (workerThread != null)
            {
                EventLog.WriteEntry("OnStop - OnStop Worker thread state = " + workerThread.ThreadState.ToString());
            }
            this.ExitCode = 0;
        }

        public static void ServiceMain()
        {
            System.ServiceProcess.ServiceBase.Run(new UO98Service());
        }

        private static ManualResetEvent pause = new ManualResetEvent(false);

        private static ServiceController GetServiceController()
        {
            return new ServiceController(UniqueServiceName);
        }

        public static void ServiceControlStop()
        {
            System.ServiceProcess.ServiceController Service = GetServiceController();
            if (Service == null)
                Console.WriteLine(" - Service Stop failed. Service is not installed.");
            else if (Service.Status == ServiceControllerStatus.Running)
            {
                Service.Stop();
                Console.WriteLine(" - Stop Signal Sent.");
            }
            else
                Console.WriteLine(" - Service Stop failed. Service is not running.");
        }

        public static bool IsRunning
        {
            get
            {
                System.ServiceProcess.ServiceController Service = GetServiceController();
                try
                {
                    return (Service != null && Service.Status == ServiceControllerStatus.Running);
                }
                catch
                {
                    return false;
                }
            }
        }

        public static void ServiceControlStart()
        {
            System.ServiceProcess.ServiceController Service = GetServiceController();
            if (Service == null)
                Console.WriteLine(" - Service Start failed. Service is not installed.");
            else if (Service.Status != ServiceControllerStatus.Running)
            {
                Service.Start();
                Console.WriteLine(" - Start Signal Sent.");
            }
            else
                Console.WriteLine(" - Service Start failed. Service is already running.");

        }

        public static void ServiceControlRestart()
        {
            System.ServiceProcess.ServiceController Service = GetServiceController();

            System.Diagnostics.EventLog.WriteEntry(UniqueServiceName, " - Service Restart attempt.");
            Console.WriteLine("Service Restart attempt...");
            if (Service == null)
                Console.WriteLine(" - Service Restart failed. Service is not installed.");
            else if (Service.Status == ServiceControllerStatus.Running)
            {
                Service.Stop();
                Console.WriteLine(" - Stop Signal Sent.");

                DateTime Timeout = DateTime.Now.AddSeconds(30);
                while (Timeout > DateTime.Now && Service.Status != ServiceControllerStatus.Stopped)
                {
                    System.Diagnostics.Trace.WriteLine("Sleeping Service Restart Thread.");
                    Thread.Sleep(500);
                    Service.Refresh();
                }

                if (Service.Status == ServiceControllerStatus.Stopped)
                {
                    Service.Start();
                    Console.WriteLine(" - Start Signal Sent.");
                }
                else
                {
                    Console.WriteLine(" - Service Restart failed. Service did not stop. Status:" + Service.Status.ToString());
                    System.Diagnostics.EventLog.WriteEntry(UniqueServiceName, " - Service Restart failed. Service did not stop.");
                }
            }
            else
            {
                Console.WriteLine(" - Service Restart failed. Service not running.");
                System.Diagnostics.EventLog.WriteEntry(UniqueServiceName, " - Service Restart failed. Service not running.");
            }
        }

        [DllImport("ADVAPI32.DLL", EntryPoint = "SetServiceStatus")]
        public static extern bool SetServiceStatus(IntPtr hServiceStatus, SERVICE_STATUS lpServiceStatus);
        private SERVICE_STATUS myServiceStatus;

        public static bool Install()
        {
            CustomServiceInstaller si = new CustomServiceInstaller();
            if (si.InstallService(Assembly.GetExecutingAssembly().Location + " -service", UO98Service.UniqueServiceName, "RunUO 2.0 Service"))
            {
                Console.WriteLine("The {0} service has been installed.", UO98Service.UniqueServiceName);
                return true;
            }
            else
            {
                Console.WriteLine("An error occurred during service installation.");
                return false;
            }
        }

        public static bool UnInstall()
        {
            CustomServiceInstaller si = new CustomServiceInstaller();
            if (si.UnInstallService(UO98Service.UniqueServiceName))
            {
                Console.WriteLine("The {0} service has been uninstalled. You may need to reboot to remove it completely.", UO98Service.UniqueServiceName);
                return true;
            }
            else
            {
                Console.WriteLine("An error occurred during service removal.");
                return false;
            }
        }
    }

    public struct SERVICE_STATUS
    {
        public int serviceType;
        public int currentState;
        public int controlsAccepted;
        public int win32ExitCode;
        public int serviceSpecificExitCode;
        public int checkPoint;
        public int waitHint;
    }

    public enum State
    {
        SERVICE_STOPPED = 0x00000001,
        SERVICE_START_PENDING = 0x00000002,
        SERVICE_STOP_PENDING = 0x00000003,
        SERVICE_RUNNING = 0x00000004,
        SERVICE_CONTINUE_PENDING = 0x00000005,
        SERVICE_PAUSE_PENDING = 0x00000006,
        SERVICE_PAUSED = 0x00000007,
    }


}
