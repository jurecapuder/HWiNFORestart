using System;
using System.Diagnostics;
using System.Linq;
using System.Threading;

class Program
{
    static bool IsHwinfoRunning()
    {
        var processes = Process.GetProcesses();
        return processes.Any(process => process.ProcessName.Equals("HWiNFO64", StringComparison.OrdinalIgnoreCase));
    }

    static void OpenHwinfo()
    {
        try
        {
            if (!IsHwinfoRunning())
            {
                Process.Start("C:\\Program Files\\HWiNFO64\\HWiNFO64.EXE");
                Console.WriteLine("HWiNFO64.EXE is opened.");
            }
            else
            {
                Console.WriteLine("HWiNFO64.EXE is already running.");
            }
        }
        catch (Exception e)
        {
            Console.WriteLine($"An error occurred: {e}");
        }
    }

    static void KillHwinfo()
    {
        try
        {
            // Check if HWiNFO64 process is running
            var processes = Process.GetProcesses();
            var hwinfoProcess = processes.FirstOrDefault(process => process.ProcessName.Equals("HWiNFO64", StringComparison.OrdinalIgnoreCase));
            
            if (hwinfoProcess != null)
            {
                hwinfoProcess.Kill();
                Console.WriteLine("HWiNFO64.EXE process terminated.");
            }
            else
            {
                Console.WriteLine("HWiNFO64.EXE process is not running.");
            }
        }
        catch (Exception e)
        {
            Console.WriteLine($"An error occurred: {e}");
        }
    }

    static void Main(string[] args)
    {
        // First, kill the HWiNFO64 process if it's running
        KillHwinfo();

        // Add a small delay (in milliseconds)
        Thread.Sleep(1000);  // You can adjust the duration as needed

        // Then, open the HWiNFO64 process
        OpenHwinfo();
    }
}
