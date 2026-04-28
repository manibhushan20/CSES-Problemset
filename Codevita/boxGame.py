def main():
  
    try:
        m, n = map(int, input().split())
    except:
        return

  
    c = [0] * n
    for _ in range(m):
        row = input().replace(" ", "")
        for j in range(n):
            if row[j] == '*':
                c[j] += 1
    

    k = int(input().strip())

    for _ in range(k):
        d = input().strip() 

      
        f = [0] * (m + 1)
        for v in c:
            f[v] += 1
        
       
        sfx = [0] * (m + 2)
        cur = 0
        for x in range(m, -1, -1):
            cur += f[x]
            sfx[x] = cur

   
        nm, nn = n, m
        nc = [0] * nn

        if d == "right":
            for col in range(nn):
                nc[col] = sfx[col + 1]
        else: 
            for col in range(nn):
                nc[col] = sfx[m - col]
        
        
        m, n = nm, nn
        c = nc
    
   
    for i in range(m):
        row = []
        for j in range(n):
            ch = '*' if i >= m - c[j] else '.'
            row.append(ch)
        print("".join(row))

if __name__ == "__main__":
    main()