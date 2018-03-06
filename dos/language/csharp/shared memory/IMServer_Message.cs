using System;
using System.IO;
using System.IO.MemoryMappedFiles;
using System.Runtime.InteropServices;
using System.Threading;

namespace IMServer_Message
{
    /// <summary>
    /// 用于共享内存方式通信的 值类型 结构体
    /// </summary>
    public struct ServiceMsg
    {
        public int Id;
        public long NowTime;
    }

    internal class Program
    {
        private static void Main(string[] args)
        {
            Console.Write("请输入共享内存公用名(默认:testmap):");
            string shareName = Console.ReadLine();
            if (string.IsNullOrEmpty(shareName))
                shareName = "testmap";
            using (MemoryMappedFile mmf = MemoryMappedFile.CreateOrOpen(shareName, 1024000,MemoryMappedFileAccess.ReadWrite))
            {
                bool mutexCreated;
                //进程间同步
                var mutex = new Mutex(true, "testmapmutex", out mutexCreated);
                using (MemoryMappedViewStream stream = mmf.CreateViewStream()) //创建文件内存视图流
                {
                    var writer = new BinaryWriter(stream);
                    for (int i = 0; i < 5; i++)
                    {
                        writer.Write(i);
                        Console.WriteLine("{0}位置写入流:{0}", i);
                    }
                }

                mutex.ReleaseMutex();

                Console.WriteLine("启动状态服务，按【回车】读取共享内存数据");
                Console.ReadLine();

                mutex.WaitOne();
                using (MemoryMappedViewStream stream = mmf.CreateViewStream())
                {
                    var reader = new BinaryReader(stream);
                    for (int i = 0; i < 10; i++)
                    {
                        Console.WriteLine("{1}位置:{0}", reader.ReadInt32(), i);
                    }
                }

                using (MemoryMappedViewAccessor accessor = mmf.CreateViewAccessor(1024, 10240))
                {
                    int colorSize = Marshal.SizeOf(typeof (ServiceMsg));
                    ServiceMsg color;
                    for (int i = 0; i < 50; i += colorSize)
                    {
                        accessor.Read(i, out color);
                        Console.WriteLine("{1}\tNowTime:{0}", new DateTime(color.NowTime), color.Id);
                    }
                }
                mutex.ReleaseMutex();
            }
            Console.WriteLine("测试： 我是 即时通讯 - 消息服务 我启动啦！！！");
            Console.ReadKey();
        }
    }
}