using System;

namespace ConsoleApp
{
    class Program
    {
        static void Main(string[] args)
        {
            var coreAssemblyInfo = System.Diagnostics.FileVersionInfo.GetVersionInfo(typeof(object).Assembly.Location);
            Console.WriteLine($"Hello World from Core {coreAssemblyInfo.ProductVersion}");
            Console.WriteLine($"The location is {typeof(object).Assembly.Location}");

            while (true)
            {
                Console.WriteLine("Take your action: (r)un, (e)xit");
                var keyInfo = Console.ReadKey();
                if (keyInfo.KeyChar == 'e')
                    break;
                if (keyInfo.KeyChar == 'r')
                    RunAllocations();
            }
        }

        private static void RunAllocations()
        {
            long beginAllocs = GC.GetAllocatedBytesForCurrentThread();
            Random rand = new Random();
            string str = string.Empty;
            for (int i = 0; i < rand.Next(128, 256); ++i)
            {
                str += "<tag>";
                str += i.ToString();
                str += "</tag>";
            }
            Console.WriteLine($"Run some allocs to build string with {str.Length} chars");
            long endAllocs = GC.GetAllocatedBytesForCurrentThread();
            Console.WriteLine($"   Allocated {endAllocs - beginAllocs}");
            Console.WriteLine($"   Total allocated {endAllocs}");
        }
    }
}
