using DevExpress.Xpf.Core;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using DevExpress.Mvvm;
using DevExpress.Xpf.Charts;

namespace CliPerformanceAnalyzer
{
    class ChartViewModel : ViewModelBase, IDisposable
    {
        #region - member variables & properties
        private TestModule testModule = null;

        Collection<DataSeries> analysisResults;
        public Collection<DataSeries> AnalysisResults
        {
            get { return analysisResults; }
            private set
            {
                analysisResults = value;
                //RaisePropertyChanged("NativeResults");
            }
        }
        #endregion

        #region - initializer
        public ChartViewModel(Object obj)
        {
            if (obj is TestModule)
            {
                testModule = obj as TestModule;
            }

            if (testModule != null)
            {
                AnalysisResults = new Collection<DataSeries>();

                InitDataCollection();
            }
        }

        #region - IEnumerable method
        void InitDataCollection()
        {
            if (testModule.Native_Test1_Time != 0.0 || testModule.Native_Test2_Time != 0.0 || testModule.Native_Test3_Time != 0.0)
            {
                AddNativeDataSeries();
            }

            if (testModule.DotNET_Test1_Time != 0.0 || testModule.DotNET_Test2_Time != 0.0 || testModule.DotNET_Test3_Time != 0.0)
            {
                AddDotNETDataSeries();
            }

            if (testModule.CliProxy_Test1_Time != 0.0 || testModule.CliProxy_Test2_Time != 0.0 || testModule.CliProxy_Test3_Time != 0.0)
            {
                AddCliProxyDataSeries();
            }

            if (testModule.CliLogic_Test1_Time != 0.0 || testModule.CliLogic_Test2_Time != 0.0 || testModule.CliLogic_Test3_Time != 0.0)
            {
                AddCliLogicDataSeries();
            }

            if (testModule.PInvoke_Test1_Time != 0.0 || testModule.PInvoke_Test2_Time != 0.0 || testModule.PInvoke_Test3_Time != 0.0)
            {
                AddPInvokeDataSeries();
            }
        }

        void AddNativeDataSeries()
        {
            analysisResults.Add(new DataSeries {
                TargetName = "Native",
                Values = new Collection<Data> {
                    new Data { TestName = "Test1", Value = testModule.Native_Test1_Time},
                    new Data { TestName = "Test2", Value = testModule.Native_Test2_Time},
                    new Data { TestName = "Test3", Value = testModule.Native_Test3_Time}
                }
            });
        }

        void AddDotNETDataSeries()
        {
            analysisResults.Add(new DataSeries {
                TargetName = ".NET",
                Values = new Collection<Data> {
                    new Data { TestName = "Test1", Value = testModule.DotNET_Test1_Time},
                    new Data { TestName = "Test2", Value = testModule.DotNET_Test2_Time},
                    new Data { TestName = "Test3", Value = testModule.DotNET_Test3_Time}
                }
            });
        }

        void AddCliProxyDataSeries()
        {
            analysisResults.Add(new DataSeries {
                TargetName = "CLI proxy",
                Values = new Collection<Data> {
                    new Data { TestName = "Test1", Value = testModule.CliProxy_Test1_Time},
                    new Data { TestName = "Test2", Value = testModule.CliProxy_Test2_Time},
                    new Data { TestName = "Test3", Value = testModule.CliProxy_Test3_Time}
                }
            });
        }

        void AddCliLogicDataSeries()
        {
            analysisResults.Add(new DataSeries {
                TargetName = "CLI logic",
                Values = new Collection<Data> {
                    new Data { TestName = "Test1", Value = testModule.CliLogic_Test1_Time},
                    new Data { TestName = "Test2", Value = testModule.CliLogic_Test2_Time},
                    new Data { TestName = "Test3", Value = testModule.CliLogic_Test3_Time}
                }
            });
        }

        void AddPInvokeDataSeries()
        {
            analysisResults.Add(new DataSeries {
                TargetName = "P/Invoke",
                Values = new Collection<Data> {
                    new Data { TestName = "Test1", Value = testModule.PInvoke_Test1_Time},
                    new Data { TestName = "Test2", Value = testModule.PInvoke_Test2_Time},
                    new Data { TestName = "Test3", Value = testModule.PInvoke_Test3_Time}
                }
            });
        }
        #endregion

        #region IDisposable Support
        private bool disposedValue = false;

        protected virtual void Dispose(bool disposing)
        {
            if (!disposedValue)
            {
                if (disposing)
                {
                    // TODO: Managed
                    testModule = null;
                }

                // TODO: Unmanaged

                disposedValue = true;
            }
        }

        // TODO: 위의 Dispose(bool disposing)에 Unmanaged 해제하는 코드가 포함되어 있는 경우
        // ~ChartViewModel() {
        //   Dispose(false);
        // }

        // Support Disposable Pattern
        public void Dispose()
        {
            Dispose(true);
            // TODO: Finalizer 가 재정의된 경우
            // GC.SuppressFinalize(this);
        }
        #endregion
        #endregion
    }
}
