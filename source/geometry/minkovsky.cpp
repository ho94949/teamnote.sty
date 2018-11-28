 i = j = 0
 V[n] = V[0], V[n+1] = V[1], W[m] = W[0], W[m+1] = W[1]
 while i < n or j < m do
   add V[i]+W[j] to answer
   if angle(V[i], V[i+1]) < angle(W[j], W[j+1])
     ++i
   else if angle(V[i], V[i+1]) > angle(W[j], W[j+1])
     ++j
   else
     ++i, ++j