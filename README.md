## 偽隨機密碼生成器 Random Password Generator

#### 簡單説明
- Prerequisite: [VS_PE_STUB]
- 隨機本身僅一個效果，沒有任何規定其與哪種具體算法相關聯，由於具體實現所產生的偽隨機算法是一個效果中心的概念 "Random" is only an effect and not bound by any specific algorithm, "Pseudo-random number generation algorith" from approaches to implementations is an effect-oriented concept
- [srand] 不保證綫程安全 srand is not guaranteed to be thread-safe


#### 已知問題 Known Bugs and/or Issues
- 若添加圖標，則16*16 2-Color 圖標在 Win10 x64 任務欄中不顯示 【微軟問題。Win7 x86下沒有此問題】




[VS_PE_STUB]: <https://github.com/ForgedSpirit/VS_PE_STUB>
[srand]: <http://en.cppreference.com/w/c/numeric/random/srand>
