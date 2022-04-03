T=int(input())
for t in range(1,T+1):
 [a,e]=map(int,input().split(' '))
 i='..+'+(e-1)*'-+'
 n='..|'+(e-1)*'.|'
 p='+-'*e+'+'
 u='|.'*e+'|'
 r=[i,n]+[p,u]*(a-1)+[p]
 print(f'Case #{t}:\n'+'\n'.join(r))
