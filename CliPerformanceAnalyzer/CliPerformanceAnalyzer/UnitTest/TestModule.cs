using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace CliPerformanceAnalyzer
{
    public class TestModule
    {
        #region - native DLL Import
        [DllImport("NativeModule.dll")]
        private static extern void NATIVE_IncrementCounter();

        [DllImport("NativeModule.dll")]
        private static extern double NATIVE_CalculateSquareRoot(double value);

        [DllImport("NativeModule.dll")]
        private static extern double NATIVE_DotProduct(double[] threeTuple1, double[] threeTuple2);

        [DllImport("NativeModule.dll")]
        private static extern void NATIVE_Test1(uint count);

        [DllImport("NativeModule.dll")]
        private static extern void NATIVE_Test2(uint count);

        [DllImport("NativeModule.dll")]
        private static extern void NATIVE_Test3(uint count);
        #endregion

        #region - member variables & properties
        private uint testCount;
        public uint TestCount
        {
            get { return testCount; }
            set { testCount = value; }
        }

        private Stopwatch stopwatch = null;

        public double Native_Test1_Time { get; set; }
        public double Native_Test2_Time { get; set; }
        public double Native_Test3_Time { get; set; }

        public double CliProxy_Test1_Time { get; set; }
        public double CliProxy_Test2_Time { get; set; }
        public double CliProxy_Test3_Time { get; set; }

        public double PInvoke_Test1_Time { get; set; }
        public double PInvoke_Test2_Time { get; set; }
        public double PInvoke_Test3_Time { get; set; }

        public double DotNET_Test1_Time { get; set; }
        public double DotNET_Test2_Time { get; set; }
        public double DotNET_Test3_Time { get; set; }

        public double CliLogic_Test1_Time { get; set; }
        public double CliLogic_Test2_Time { get; set; }
        public double CliLogic_Test3_Time { get; set; }
        #endregion

        #region - initializer
        public TestModule()
        {
            testCount = 1000000;

            stopwatch = new Stopwatch();
        }
        #endregion

        #region - member method for testing

        public void RunNativeTest()
        {
            stopwatch.Restart();
            NATIVE_Test1(testCount);
            stopwatch.Stop();
            Native_Test1_Time = stopwatch.Elapsed.TotalMilliseconds;

            stopwatch.Restart();
            NATIVE_Test2(testCount);
            stopwatch.Stop();
            Native_Test2_Time = stopwatch.Elapsed.TotalMilliseconds;

            stopwatch.Restart();
            NATIVE_Test3(testCount);
            stopwatch.Stop();
            Native_Test3_Time = stopwatch.Elapsed.TotalMilliseconds;
        }

        public void RunDotNETTest()
        {
            stopwatch.Restart();
            for (uint i = 1; i <= testCount; ++i)
            {
                DotNET_IncrementCounter();
            }
            stopwatch.Stop();
            DotNET_Test1_Time = stopwatch.Elapsed.TotalMilliseconds;

            stopwatch.Restart();
            for (uint i = 1; i <= testCount; ++i)
            {
                double d = DotNET_CalculateSquareRoot((double)i);
            }
            stopwatch.Stop();
            DotNET_Test2_Time = stopwatch.Elapsed.TotalMilliseconds;

            stopwatch.Restart();
            for (uint i = 1; i <= testCount; ++i)
            {
                double[] threeTuple1 = new double[] { i, i, i };
                double[] threeTuple2 = new double[] { i, i, i };
                double d = DotNET_DotProduct(threeTuple1, threeTuple2);
            }
            stopwatch.Stop();
            DotNET_Test3_Time = stopwatch.Elapsed.TotalMilliseconds;
        }

        public void RunCliProxyTest()
        {
            ManagedModule.NativeWrapperCli managedInterface = new ManagedModule.NativeWrapperCli();
            if (managedInterface != null)
            {
                stopwatch.Restart();
                for (uint i = 1; i <= testCount; ++i)
                {
                    managedInterface.IncrementCounter();
                }
                stopwatch.Stop();
                CliProxy_Test1_Time = stopwatch.Elapsed.TotalMilliseconds;

                stopwatch.Restart();
                for (uint i = 1; i <= testCount; ++i)
                {
                    double d = managedInterface.CalculateSquareRoot((double)i);
                }
                stopwatch.Stop();
                CliProxy_Test2_Time = stopwatch.Elapsed.TotalMilliseconds;

                stopwatch.Restart();
                for (uint i = 1; i <= testCount; ++i)
                {
                    double[] threeTuple1 = new double[] { i, i, i };
                    double[] threeTuple2 = new double[] { i, i, i };
                    double d = managedInterface.DotProduct(threeTuple1, threeTuple2);
                }
                stopwatch.Stop();
                CliProxy_Test3_Time = stopwatch.Elapsed.TotalMilliseconds;
            }
        }

        public void RunCliLogicTest()
        {
            ManagedModule.NativeWrapperCli managedInterface = new ManagedModule.NativeWrapperCli();
            if (managedInterface != null)
            {
                stopwatch.Restart();
                managedInterface.IncrementCounterCli(testCount);
                stopwatch.Stop();
                CliLogic_Test1_Time = stopwatch.Elapsed.TotalMilliseconds;

                stopwatch.Restart();
                managedInterface.CalculateSquareRootCli(testCount, (double)10);
                stopwatch.Stop();
                CliLogic_Test2_Time = stopwatch.Elapsed.TotalMilliseconds;

                stopwatch.Restart();
                double[] threeTuple1 = new double[] { 1.0, 2.0, 3.0 };
                double[] threeTuple2 = new double[] { 1.0, 2.0, 3.0 };
                managedInterface.DotProductCli(testCount, threeTuple1, threeTuple2);
                stopwatch.Stop();
                CliLogic_Test3_Time = stopwatch.Elapsed.TotalMilliseconds;
            }
        }

        public void RunPInvokeTest()
        {
            stopwatch.Restart();
            for (uint i = 1; i <= testCount; ++i)
            {
                NATIVE_IncrementCounter();
            }
            stopwatch.Stop();
            PInvoke_Test1_Time = stopwatch.Elapsed.TotalMilliseconds;

            stopwatch.Restart();
            for (uint i = 1; i <= testCount; ++i)
            {
                double d = NATIVE_CalculateSquareRoot((double)i);
            }
            stopwatch.Stop();
            PInvoke_Test2_Time = stopwatch.Elapsed.TotalMilliseconds;

            stopwatch.Restart();
            for (uint i = 1; i <= testCount; ++i)
            {
                double[] threeTuple1 = new double[] { i, i, i };
                double[] threeTuple2 = new double[] { i, i, i };
                double d = NATIVE_DotProduct(threeTuple1, threeTuple2);
            }
            stopwatch.Stop();
            PInvoke_Test3_Time = stopwatch.Elapsed.TotalMilliseconds;
        }

        #region - .NET variable & method
        uint increCounter = 0;
        double sqrtResult = 0.0;
        double dotproductResult = 0.0;

        void DotNET_IncrementCounter()
        {
            ++increCounter;
        }

        double DotNET_CalculateSquareRoot(double dValue)
        {
            sqrtResult += Math.Sqrt(dValue);
            return sqrtResult;
        }


        double DotNET_DotProduct(double[] arThreeTuple1, double[] arThreeTuple2)
        {
            dotproductResult += arThreeTuple1[0] * arThreeTuple2[0] + arThreeTuple1[1] * arThreeTuple2[1] + arThreeTuple1[2] * arThreeTuple2[2];
            return dotproductResult;
        }
        #endregion
        #endregion

    }
}
