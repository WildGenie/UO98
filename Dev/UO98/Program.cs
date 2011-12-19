using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.IO;

namespace UO98
{
    class Program
    {
        static ServerProcess process;

        static void Main(string[] args)
        {
            process = new ServerProcess(Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location));
            process.Start();
            while(true)
            {
                Thread.Sleep(1000);
            }
        }


    }

}
