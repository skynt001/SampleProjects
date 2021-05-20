using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using DevExpress.Xpf.Core;

namespace CliPerformanceAnalyzer
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : ThemedWindow
    {
        MainViewModel mvm = null;

        public MainWindow()
        {
            InitializeComponent();

            mvm = new MainViewModel();
            this.DataContext = mvm;
        }

        void UpdateDataGrid()
        {
            //mvm.
            //IDC_DataGrid.GetRootParent().
        }
    }
}
