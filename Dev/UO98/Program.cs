using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.IO;
using System.Runtime.InteropServices;
using System.ServiceProcess;

namespace UO98
{
    class Program
    {
        private static bool isclosing = false;

        static ServerProcess process;

        static void Main(string[] args)
        {
            #region Service Control

            if (args.Length == 1 && (Insensitive.Equals(args[0], "-service")
                || Insensitive.Equals(args[0], "installservice")
                || Insensitive.Equals(args[0], "uninstallservice")
                || Insensitive.Equals(args[0], "restartservice")
                || Insensitive.Equals(args[0], "stopservice")
                || Insensitive.Equals(args[0], "startservice")))
            {
                if (Insensitive.Equals(args[0], "-service"))
                {
                    Directory.SetCurrentDirectory((new FileInfo(System.Reflection.Assembly.GetExecutingAssembly().Location).DirectoryName));
                    UO98Service.Main();
                    return;
                }
                else if (Insensitive.Equals(args[0], "restartservice"))
                {
                    UO98Service.ServiceControlRestart();
                }
                else if (Insensitive.Equals(args[0], "stopservice"))
                {
                    UO98Service.ServiceControlStop();
                }
                else if (Insensitive.Equals(args[0], "startservice"))
                {
                    UO98Service.ServiceControlStart();
                }
                else if (Insensitive.Equals(args[0], "installservice") )
                {
                    UO98Service.Install();
                }
                else if (Insensitive.Equals(args[0], "uninstallservice"))
                {
                    UO98Service.UnInstall();
                }
            }
            #endregion

            bool respawn=false;
            if(args.Length >= 1)
            {
                if(args.Length == 1 && Insensitive.Equals(args[0], "respawn"))
                    respawn = true;
                else
                {
                    Console.WriteLine("Usage: UO98 [respawn|installservice|uninstallservice|startservice|stopservice|restartservice]");

                    return;
                }
            }

            Run(respawn);
        }

        internal static void Run()
        {
            Run(false);
        }

        internal static void Run(bool respawn)
        {
            SetConsoleCtrlHandler(ConsoleCtrlCheck, true);

            if(process == null)
            {
                process = new ServerProcess(Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location));
                process.OnProcessExited += new EventHandler<ServerProcess.OnExitedEventArgs>(process_OnProcessExited);
            }

            try
            {
                do
                {
                    process.Start();
                    while(process.IsRunning && !isclosing)
                    {
                        Thread.Sleep(250);
                    }
                } while(respawn && !isclosing);
            }
            finally
            {
                process.Stop();
            }
        }

        public class OnEventLogMessageArgs : EventArgs { public string Message { get; set; } }
        public static event EventHandler<OnEventLogMessageArgs> OnEventLogMessage;
        public static event EventHandler<ServerProcess.OnExitedEventArgs> OnProcessExited;

        static void process_OnProcessExited(object sender, ServerProcess.OnExitedEventArgs e)
        {
            string message = string.Format("Process exited with code {0}", e.ExitCode);
            if(OnEventLogMessage != null) OnEventLogMessage(sender, new OnEventLogMessageArgs() { Message = message });
            if(OnProcessExited != null) OnProcessExited(sender, e);
        }

        [DllImport("Kernel32")]
        public static extern bool SetConsoleCtrlHandler(HandlerRoutine Handler, bool Add);
        public delegate bool HandlerRoutine(CtrlTypes CtrlType);

        public enum CtrlTypes
        {
            CTRL_C_EVENT = 0,
            CTRL_BREAK_EVENT,
            CTRL_CLOSE_EVENT,
            CTRL_LOGOFF_EVENT = 5,
            CTRL_SHUTDOWN_EVENT
        }

        private static bool ConsoleCtrlCheck(CtrlTypes ctrlType)
        {
            switch (ctrlType)
            {
                case CtrlTypes.CTRL_C_EVENT:
                case CtrlTypes.CTRL_BREAK_EVENT:
                case CtrlTypes.CTRL_CLOSE_EVENT:
                case CtrlTypes.CTRL_LOGOFF_EVENT:
                case CtrlTypes.CTRL_SHUTDOWN_EVENT:
                    process.Stop();
                    isclosing = true;
                    Console.WriteLine("Exiting.");
                    break;
            }
            return true;
        }
    }

}
