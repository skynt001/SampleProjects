using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Windows.Input;
using DevExpress.Mvvm;
using System.Windows.Controls;

namespace CliPerformanceAnalyzer
{
    class MainViewModel : ViewModelBase
    {
        #region - member variables & properties
        // test case for threading
        private BackgroundWorker backgroundWorker = new BackgroundWorker();
        TestModule testModule = new TestModule();

        ChartWindow chartWnd = null;

        private uint IterationsProperty = 1000000;
        public uint Iterations
        {
            get { return IterationsProperty; }
            set {
                IterationsProperty = value;
                RaisePropertyChanged("Iterations");
            }
        }

        private string StatusProperty = "Ready";
        public string Status
        {
            get { return StatusProperty; }
            set
            {
                StatusProperty = value;
                RaisePropertyChanged("Status");
            }
        }

        private double Native_Test1_ResultProperty;
        public double Native_Test1_Result
        {
            get { return Native_Test1_ResultProperty; }
            set {
                Native_Test1_ResultProperty = value;
                RaisePropertyChanged("Native_Test1_Result");
            }
        }

        private double Native_Test2_ResultProperty;
        public double Native_Test2_Result
        {
            get { return Native_Test2_ResultProperty; }
            set {
                Native_Test2_ResultProperty = value;
                RaisePropertyChanged("Native_Test2_Result");
            }
        }

        private double Native_Test3_ResultProperty;
        public double Native_Test3_Result
        {
            get { return Native_Test3_ResultProperty; }
            set {
                Native_Test3_ResultProperty = value;
                RaisePropertyChanged("Native_Test3_Result");
            }
        }

        private double DotNET_Test1_ResultProperty;
        public double DotNET_Test1_Result
        {
            get { return DotNET_Test1_ResultProperty; }
            set
            {
                DotNET_Test1_ResultProperty = value;
                RaisePropertyChanged("DotNET_Test1_Result");
            }
        }

        private double DotNET_Test2_ResultProperty;
        public double DotNET_Test2_Result
        {
            get { return DotNET_Test2_ResultProperty; }
            set
            {
                DotNET_Test2_ResultProperty = value;
                RaisePropertyChanged("DotNET_Test2_Result");
            }
        }

        private double DotNET_Test3_ResultProperty;
        public double DotNET_Test3_Result
        {
            get { return DotNET_Test3_ResultProperty; }
            set
            {
                DotNET_Test3_ResultProperty = value;
                RaisePropertyChanged("DotNET_Test3_Result");
            }
        }

        private double CliProxy_Test1_ResultProperty;
        public double CliProxy_Test1_Result
        {
            get { return CliProxy_Test1_ResultProperty; }
            set {
                CliProxy_Test1_ResultProperty = value;
                RaisePropertyChanged("CliProxy_Test1_Result");
            }
        }

        private double CliProxy_Test2_ResultProperty;
        public double CliProxy_Test2_Result
        {
            get { return CliProxy_Test2_ResultProperty; }
            set {
                CliProxy_Test2_ResultProperty = value;
                RaisePropertyChanged("CliProxy_Test2_Result");
            }
        }

        private double CliProxy_Test3_ResultProperty;
        public double CliProxy_Test3_Result
        {
            get { return CliProxy_Test3_ResultProperty; }
            set {
                CliProxy_Test3_ResultProperty = value;
                RaisePropertyChanged("CliProxy_Test3_Result");
            }
        }

        private double CliLogic_Test1_ResultProperty;
        public double CliLogic_Test1_Result
        {
            get { return CliLogic_Test1_ResultProperty; }
            set
            {
                CliLogic_Test1_ResultProperty = value;
                RaisePropertyChanged("CliLogic_Test1_Result");
            }
        }

        private double CliLogic_Test2_ResultProperty;
        public double CliLogic_Test2_Result
        {
            get { return CliLogic_Test2_ResultProperty; }
            set
            {
                CliLogic_Test2_ResultProperty = value;
                RaisePropertyChanged("CliLogic_Test2_Result");
            }
        }

        private double CliLogic_Test3_ResultProperty;
        public double CliLogic_Test3_Result
        {
            get { return CliLogic_Test3_ResultProperty; }
            set
            {
                CliLogic_Test3_ResultProperty = value;
                RaisePropertyChanged("CliLogic_Test3_Result");
            }
        }

        private double PInvoke_Test1_ResultProperty;
        public double PInvoke_Test1_Result
        {
            get { return PInvoke_Test1_ResultProperty; }
            set {
                PInvoke_Test1_ResultProperty = value;
                RaisePropertyChanged("PInvoke_Test1_Result");
            }
        }

        private double PInvoke_Test2_ResultProperty;
        public double PInvoke_Test2_Result
        {
            get { return PInvoke_Test2_ResultProperty; }
            set {
                PInvoke_Test2_ResultProperty = value;
                RaisePropertyChanged("PInvoke_Test2_Result");
            }
        }

        private double PInvoke_Test3_ResultProperty;
        public double PInvoke_Test3_Result
        {
            get { return PInvoke_Test3_ResultProperty; }
            set {
                PInvoke_Test3_ResultProperty = value;
                RaisePropertyChanged("PInvoke_Test3_Result");
            }
        }

        private bool NativeCheckProperty = true;
        public bool NativeCheck
        {
            get { return NativeCheckProperty; }
            set
            {
                NativeCheckProperty = value;
                RaisePropertyChanged("NativeCheck");
            }
        }
        private bool CliProxyCheckProperty = true;
        public bool CliProxyCheck
        {
            get { return CliProxyCheckProperty; }
            set
            {
                CliProxyCheckProperty = value;
                RaisePropertyChanged("CliProxyCheck");
            }
        }
        private bool CliLogicCheckProperty = false;
        public bool CliLogicCheck
        {
            get { return CliLogicCheckProperty; }
            set
            {
                CliLogicCheckProperty = value;
                RaisePropertyChanged("CliLogicCheck");
            }
        }
        private bool DotNETCheckProperty = false;
        public bool DotNETCheck
        {
            get { return DotNETCheckProperty; }
            set
            {
                DotNETCheckProperty = value;
                RaisePropertyChanged("DotNETCheck");
            }
        }
        private bool PInvokeCheckProperty = true;
        public bool PInvokeCheck
        {
            get { return PInvokeCheckProperty; }
            set
            {
                PInvokeCheckProperty = value;
                RaisePropertyChanged("PInvokeCheck");
            }
        }
        #endregion

        #region - commands
        public DelegateCommand RunTestCommand { get; private set; }
        public bool CanRunTestProperty = true;
        public bool CanRunTest {
            get { return CanRunTestProperty; }
            private set {
                CanRunTestProperty = value;
                RaisePropertyChanged("CanRunTest");
            }
        }

        public DelegateCommand VisualizationCommand { get; private set; }
        public bool CanVisualizationProperty = true;
        public bool CanVisualization {
            get { return CanVisualizationProperty; }
            private set {
                CanVisualizationProperty = value;
                RaisePropertyChanged("CanVisualization");
            }
        }
        #endregion

        #region - initializer
        public MainViewModel()
        {
            backgroundWorker.DoWork += new DoWorkEventHandler(backgroundWorker_DoWork);
            backgroundWorker.RunWorkerCompleted += new RunWorkerCompletedEventHandler(backgroundWorker_RunWorkerCompleted);

            RunTestCommand = new DelegateCommand(DoRunTests);
            VisualizationCommand = new DelegateCommand(DoVisualizations);
        }
        #endregion

        #region - member mothod & events
        void backgroundWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            if (testModule != null)
            {
                this.Status = "Running..";

                testModule.TestCount = Iterations;

                if (NativeCheck)
                    testModule.RunNativeTest();

                if (DotNETCheck)
                    testModule.RunDotNETTest();

                if (CliProxyCheck)
                    testModule.RunCliProxyTest();

                if (CliLogicCheck)
                    testModule.RunCliLogicTest();

                if (PInvokeCheck)
                    testModule.RunPInvokeTest();

                e.Result = testModule;
            }
        }

        void backgroundWorker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (e.Result == null || e.Error != null)
                return;

            //  Set ViewModel properties.
            TestModule test = e.Result as TestModule;

            if (NativeCheck)
            {
                Native_Test1_Result = test.Native_Test1_Time;
                Native_Test2_Result = test.Native_Test2_Time;
                Native_Test3_Result = test.Native_Test3_Time;
            }
            else
            {
                Native_Test1_Result = test.Native_Test1_Time = 0.0;
                Native_Test2_Result = test.Native_Test2_Time = 0.0;
                Native_Test3_Result = test.Native_Test3_Time = 0.0;
            }

            if (DotNETCheck)
            {
                DotNET_Test1_Result = test.DotNET_Test1_Time;
                DotNET_Test2_Result = test.DotNET_Test2_Time;
                DotNET_Test3_Result = test.DotNET_Test3_Time;
            }
            else
            {
                DotNET_Test1_Result = test.DotNET_Test1_Time = 0.0;
                DotNET_Test2_Result = test.DotNET_Test2_Time = 0.0;
                DotNET_Test3_Result = test.DotNET_Test3_Time = 0.0;
            }

            if (CliProxyCheck)
            {
                CliProxy_Test1_Result = test.CliProxy_Test1_Time;
                CliProxy_Test2_Result = test.CliProxy_Test2_Time;
                CliProxy_Test3_Result = test.CliProxy_Test3_Time;
            }
            else
            {
                CliProxy_Test1_Result = test.CliProxy_Test1_Time = 0.0;
                CliProxy_Test2_Result = test.CliProxy_Test2_Time = 0.0;
                CliProxy_Test3_Result = test.CliProxy_Test3_Time = 0.0;
            }

            if (CliLogicCheck)
            {
                CliLogic_Test1_Result = test.CliLogic_Test1_Time;
                CliLogic_Test2_Result = test.CliLogic_Test2_Time;
                CliLogic_Test3_Result = test.CliLogic_Test3_Time;
            }
            else
            {
                CliLogic_Test1_Result = test.CliLogic_Test1_Time = 0.0;
                CliLogic_Test2_Result = test.CliLogic_Test2_Time = 0.0;
                CliLogic_Test3_Result = test.CliLogic_Test3_Time = 0.0;
            }

            if (PInvokeCheck)
            {
                PInvoke_Test1_Result = test.PInvoke_Test1_Time;
                PInvoke_Test2_Result = test.PInvoke_Test2_Time;
                PInvoke_Test3_Result = test.PInvoke_Test3_Time;
            }
            else
            {
                PInvoke_Test1_Result = test.PInvoke_Test1_Time = 0.0;
                PInvoke_Test2_Result = test.PInvoke_Test2_Time = 0.0;
                PInvoke_Test3_Result = test.PInvoke_Test3_Time = 0.0;
            }

            CanRunTest = true;
            CanVisualization = true;

            //System.Windows.MessageBox.Show("Done!", "Performance Analysis", System.Windows.MessageBoxButton.OK, System.Windows.MessageBoxImage.Information);
            this.Status = "Done!";

            if (chartWnd != null && chartWnd.IsVisible)
            {
                DoVisualizations();
            }
        }

        private void DoRunTests()
        {
            if (backgroundWorker.IsBusy != true)
            {
                this.CanRunTest = false;
                this.CanVisualization = false;

                // run the background worker
                backgroundWorker.RunWorkerAsync();
            }
        }

        private bool CanRunTests()
        {
            return this.CanRunTest;
        }

        private void DoVisualizations()
        {
            if (chartWnd != null && chartWnd.IsLoaded)
            {
                chartWnd.Close();
                chartWnd.Dispose();
            }

            ChartViewModel chartViewModel = new ChartViewModel(testModule);
            chartWnd = new ChartWindow(chartViewModel);
            chartWnd.Show();
        }

        private bool CanVisualizations()
        {
            return this.CanVisualization;
        }
        #endregion
    }

}
