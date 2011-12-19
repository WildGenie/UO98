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
    class ServerProcess
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
        };

        bool IsExiting { get; set; }

        Process MyProcess;

        public ServerProcess(string workingfolder)
        {
            BinDirectory = workingfolder;
            EnvVars["UODEMODLL"] = Path.Combine(BinDirectory, EnvVars["UODEMODLL"]);
        }

        public void Start()
        {
            if(!IsRunning)
            {
                IsExiting = false;
                Run();
            }
        }

        public void Stop()
        {
            IsExiting = true;
            if(MyProcess != null)
            {
                MyProcess.Kill();
            }
        }

        bool IsRunning { get; set; }
        bool ShouldRun { get { return MyProcess == null || !IsExiting || !IsRunning; } }

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
            foreach(KeyValuePair<string, string> var in EnvVars)
                pInfo.EnvironmentVariables[var.Key] = var.Value;
        }

        void Run()
        {
            while(ShouldRun)
            {
                MyProcess = CreateProcess();
                MyProcess.Start();

                while(IsRunning = !MyProcess.HasExited)
                    Thread.Sleep(1000);
            }
            MyProcess = null;
        }
    }
}
