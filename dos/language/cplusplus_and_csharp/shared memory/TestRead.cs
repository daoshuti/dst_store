using System;
using System.Threading;
using System.IO;
using System.IO.MemoryMappedFiles;

namespace TestRead
{
    internal class Program
    {
        private static void Main(string[] args)
        {
            Console.Write("请输入共享内存公用名(默认:testmap):");
            string shareName = Console.ReadLine();
            if (string.IsNullOrEmpty(shareName))
                shareName = "testmap";
            //using (MemoryMappedFile mmf = MemoryMappedFile.CreateOrOpen(shareName, 1024,MemoryMappedFileAccess.ReadWrite))
            using (MemoryMappedFile mmf = MemoryMappedFile.OpenExisting(shareName))
            {
                //进程间同步
                Mutex mutex = Mutex.OpenExisting("testmapmutex");
                while(true)
                {
                    Console.WriteLine("按【回车】读取共享内存数据：");
                    Console.ReadLine();
                    //Thread.Sleep(1000);
                    //mutex.WaitOne();
                    using (MemoryMappedViewStream stream = mmf.CreateViewStream())
                    {
                        var reader = new BinaryReader(stream);
                        char[] buffer = new char[1024];
                        reader.Read(buffer, 0, 1024);
                        Console.WriteLine(buffer);
                        //Console.Write(buffer);
                        //Console.WriteLine("stream lenght : " + mmf.CreateViewStream().Length.ToString());
                    }
                    //mutex.ReleaseMutex();
                }
            }
            //Console.ReadKey();
        }
    }
}
