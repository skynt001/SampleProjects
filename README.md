
# SampleProjects repo
### C 계열의 sample project들을 모아두는 공간


### 0. AutomaticDisposal (C++ / CLI)
- managed class에서 묵시적으로 사용되는 (IDisposable).Dispose를 활용한 멤버 자원 관리 방안
- Util 형식의 disposedFlag class를 활용한 멤버 자원 관리 방안

### 1. AccessExportTest (C#)
- Convert MDB to CSV 시간 측정
- Convert MDB to XML 시간 측정

### 2. MDBConverter (C++)
- 프로젝트의 일부임, 사용 시 BaseConverter 구현 혹은 상속을 받지 않아야 함
- ConverterMgr 등의 관리 객체를 구현하여 사용하기를 권장
- Using Microsoft Access Automation
- Convert MDB to XML
- Convert MDB to CSV

### 3. CliPerformanceAnalyzer (C++ / CLI / WPF)
- Native C++ layer와 .NET layer 간의 Logic 수행에 대한 성능 측정을 위함
- CLI를 이용한 Facade 구조를 Design할 때 Legacy 운용성에 관련된 실험
- Unmanaged(Native C++) 와 Managed(CLI / C#) 그리고 P/Invoke
- Required DevExpress for Visualization(Chart) & MVVM
