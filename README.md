# socket programming 程式介紹 
Socket Programming 這個程式作業以 GUI 與 multi-threading 的方式實作並展示了以下關於TCP socket的功能: 
* server 與server port 的選用
* socket 連線的建立與斷線
* 具non-blocking 功能的socket client 端
* 支持多重連線的socket server端
* client 與server 之間的socket通訊
* 即時顯示各條socket連線的狀態與通訊的內容
本作業包含了兩個獨立執行的程式: client程式與server程式 
# 使用工具介紹 
本程式作業使用的是 Microsoft Visual C++語言，UI 的部分使用的是Windows Forms，它是微軟的.NET 開發框架的圖形使用者介面。程式是在Microsoft Visual Studio 2022 環境下建構完成的。 
# 功能說明 
* **server 與 server port 的選用**: client 端的使用者可在視窗上輸入 socket server 的 IP address 與 TCP port number，做為下一次建立 TCP socket 連線時的參數。而 server 端的使用者則可設定提供服務的 TCP port number。 
* **socket 連線的建立與斷線**: 由 client 端的使用者發起。當一條連線建立時，server 程式會配置一條 socket 以及一個 thread 來專門與之通訊；而當連線斷線時，server 程式將會回收此連線使用的 socket 與 thread。 
* **具 non-blocking 功能的 socket client 端**:client 程式將 socket 設定為 non-blocking 模式，以便使用 select() 來達成建立連線時的 timeout 機制，以及全雙工模式的資料傳送與接收。(p.s.全雙工模式:指送收可以同時進行) 
* **支持多重連線的socket server端**: server 程式裡用一個 server thread 來監測 TCP socket 有沒有 client 要來連線，當新連線成功建立後，server thread便會創建一個新的connection thread來服務該client，因此本 socket server 可以支持多重連線。 
* **client 與 server 之間的 socket 通訊**: 由 client 端的使用者在視窗上輸入通訊內容然後送出，server 程式收到後便在此封內容的前端加上”server echo >> ”再回送給 client。 
* **即時顯示各條socket連線的狀態與通訊的內容**: server 和 client的 GUI 上分別建立一個 0.5 秒的 timer，用來定期檢查 socket 連線的狀態，若有狀態變化便會將新的狀態顯示在 GUI 上。此外，client 程式也利用此 timer 來檢查並接收來自 socket 連線的通訊內容，使 client 程式達成全雙工模式的資料傳送與接收。
