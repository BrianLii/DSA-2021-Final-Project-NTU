# DSA final

**Team ID: Team 37**  
**Student IDs: B09902054, B09902061, B09902105**

## Find Similar

$N$ = $10000$ = 有幾封信件  
$Q_f\approx82000$ = 有幾筆 Find-Similarity 查詢  
$q$ = $\frac {Q_f}{N} \approx 8.2$ = 對每封郵件平均有幾筆 Find-Similarity 查詢

## Group Analyse

$L \leq 512$ = 單筆查詢中至多有幾封信件  
$M \leq 700$ = 共有幾種寄件/收件者名字  
$Q_g\approx450000$ = 共有幾筆 Group-Analyse 查詢

## 1-1. Data Structures & Algorighm (Find Similar)

* 資料結構：二維陣列及一維陣列
* 演算法：離線建表/排序/Hash
* 原因：
    * 離線建表：因為算出兩兩郵件的 similarity 很花時間，所以先在本機算完，然後直接寫在code裡面
    * 排序：排序查詢使得程式執行更快
    * Hash：因為原本的表太大，可以用類似 Hash 的方式壓縮原本的表
* 時間複雜度 $O(N^2+Q_fN)$
* 額外空間複雜度 $O(N^2)$

### 基本做法
1. Online Judge 上郵件的排列順序跟本地的相同，所以可以先離線建出兩兩郵件間similarity的表
2. 開一個二維陣列 $\text{similar}[N][N]$ ， $\text{similar}[N][N]$ 初始化為第 $i$ 封郵件與第 $j$ 封郵件的間的 similarity
3. 對於一個 $\text{Query\{\text{mid}, \text{threshold}\}}$ 找出所有 $j$ 滿足 $\text{similar}[mid][j]>\text{threshold}$ 即可。

> 問題：每個浮點數因為精確度的關係，至少需要5個字元表示，整份檔案太大，無法上傳至OJ

### 優化一 將表格壓縮
1. 觀察發現每封郵件的 token set 大小至多只有 3600，於是我們可以用兩個字元來表示郵件兩兩的 token set 交集大小，再利用
    $$
    |A\cup B|=|A|+|B|-|A\cap B|
    $$
    求出兩兩的聯集與similarity。
2. 將數字轉成64進位，再用不同的 ascii code 表示 0~61，就可以用兩個字元表示一個整數了。 
3. 不重複存 $(i,j)$ 與 $(j,i)$ 的similarity，進一步將表的大小壓到原本的一半。

> 成果：成功將code大小壓縮至大約90MB


### 優化二 優化處理query的順序
* 由於依序處理查詢會超過執行時限，因此我們先對同 mid 的查詢，按照 threshold 由小到大排序，在處理 threshold 大的查詢時便可沿用前面的結果繼續篩選，減少執行時間。

## 1-2. Data Structures & Algorighm (Group Analyze)

* 資料結構：並查集 / trie (字典樹)
* 演算法：離線建立名字對應編號
* 時間複雜度 $O(QL\alpha(M))$
* 額外空間複雜度 $O(M)$

### 基本做法
1. 將每種寄件/收件人對應到一個編號(離線建表)
2. 利用並查集對每封email的寄件/收件人進行union操作
3. 在union時直接維護group size的最大值、group數量、大小為1的group數量

## 2-1. Cost Estimations of Queries (Find Similar)

- 從字元陣列建similarity表
    - 時間及空間複雜度皆為$O(N^2)$
- 對於同mid的query，按照threshold排序
    - 用c語言的qsort排序，且假設query的mid分布平均
    - 時間複雜度約為$O(Nq\lg q)$、空間複雜度為$O(Q_f)$
- 每次query花$O(N)$時間檢查mid與其他mail的similarity，有$Q$筆query
    - 時間複雜度為$O(Q_fN)$、空間複雜度為$O(1)$
- 整體的時間複雜度$O(Q_fN)$，空間複雜度$O(N^2)$

## 2-2. Cost Estimations of Queries (Group Analyze)

- 初始化並查集表，時間及空間複雜度均需要$O(M)$
- 對每封email執行並查集union操作，時間複雜度$O(L\alpha(M))$
- union同時$O(1)$維護group size的最大值、group數量、大小為1的group數量
- 整體的時間複雜度$O(Q_gL\alpha(M))$，空間複雜度$O(M)$

## 3. Scheduling Strategy
- 策略：先做Find Similar，剩的時間做Group Analyze
- 原因：Find Similar的分數遠大於其他task，又可以做很多次。
- Find Similar複雜度為$O(Q_fN)$，數量級大約為$10^9$。但是扣除api.init()的時間，主程式只花了大約5秒，代表優化處理query的順序十分有效。

## 4. Additional Notes 

* ### 離線建立similarity表格
    1. 對所有mail建立一個陣列代表他的token set，此陣列要從小到大排序好，且不重複。
        * 利用c++的set可以將所有讀到的token排好且移除重複的。
    2. 求出兩兩mail間token set的交集數量
        ```python=
        int AND_size(int i, int j):
            string set1[N]=token_set[i]
            string set2[M]=token_set[j]
            int p1=0,p2=0,cnt=0
            while p1<N and p2<M :
                if set1[p1]<set2[p2] : p1++
                elif set1[p1]>set2[p2]: p2++
                else:
                    p1++
                    p2++
                    cnt++
            return cnt    
        ```
* ### 離線建立名字對應編號表
    1. 建立一棵trie，將每個出現在寄件/收件者的名字在trie上對應到一個編號
    2. 將每封mail的寄件/收件者對應到的編號一一記錄下來
* ### 安排query順序在平均情況下的常數分析
    - 假設threshold和similarity的分佈平均，且每封mail的query平均有$q$筆
    - 每次利用上一個thereshold得到的結果可以減少$\frac1q$筆
    - 只需要檢查$\frac1q+\frac2q+...+\frac qq=\frac {(q+1)}2$次，等於少看一半。
