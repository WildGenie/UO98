using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.IO;
using System.Threading.Tasks;
using System.Threading;

namespace UO98
{
    sealed class ServerProcess
    {
        readonly string BinDirectory = string.Empty;
        readonly string UODemoPlusFilename = "UODemo+.exe";

        static readonly Dictionary<string, string> EnvVars = new Dictionary<string, string>()
        {
            {"REGKEYNAME","UO98"},
            {"SERVERNAME","UO98"},
            {"RUNDIR","rundir"},
            {"REALDAMAGE","YES"},
            {"USEACCOUNTNAME","YES"},
            {"SAVEDYNAMIC0","NO"},
            {"UODEMODLL","Sidekick.dll"},
            //{"NOCONSOLE","YES"},
        };

        bool DoExit { get; set; }

        Process MyProcess;

        public ServerProcess(string workingfolder)
        {
            BinDirectory = workingfolder;
            EnvVars["UODEMODLL"] = Path.Combine(BinDirectory, EnvVars["UODEMODLL"]);
        }

        public StreamReader StdOut
        {
            get
            {
                try
                {
                    return MyProcess == null ? null : MyProcess.StandardOutput;
                }
                catch (InvalidOperationException)
                {
                    return null;
                }
            }
        }

        object lockStartStop = new object();
        public void Start()
        {
            lock (lockStartStop)
            {
                if (Running) return;
                Running = true;
                DoExit = false;
                MyProcess = CreateProcess();
                MyProcess.Start();
            }
        }

        public void Stop()
        {
            lock (lockStartStop)
            {
                DoExit = true;
            
                if (MyProcess != null && !MyProcess.HasExited)
                {
                    MyProcess.Kill();
                    MyProcess.WaitForExit(1000);
                    MyProcess = null;
                }
                Running = false;
            }
        }

        bool Running { get; set; }
        public bool IsRunning
        {
            get
            {
                lock (lockStartStop)
                {
                    if (MyProcess == null || MyProcess.HasExited)
                        Running = false;
                    return Running;
                }
            }
        }

        Process CreateProcess()
        {
            var p = new Process();
            SetUpEnvironment(p.StartInfo);
            p.StartInfo.UseShellExecute = false;
            p.StartInfo.FileName = Path.Combine(BinDirectory, UODemoPlusFilename);
            return p;
        }

        void SetUpEnvironment(ProcessStartInfo pInfo)
        {
            foreach (KeyValuePair<string, string> var in EnvVars)
                pInfo.EnvironmentVariables[var.Key] = var.Value;
            pInfo.RedirectStandardInput = true;
            pInfo.WorkingDirectory = BinDirectory;
        }

    }
}
