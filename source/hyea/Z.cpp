vector<int> Z(const vector<int>& S) {
    int N = S.size();
    vector<int> Z(N);
    int L = 0, R = 0;
    for(int i = 1; i < N; i++) {
        if(i+Z[i-L] < R) Z[i] = Z[i-L];
        else {
            L = i, R = max(R, i);
            while(R<N && S[R] == S[R-i]) ++R;
            Z[i] = R-i;
        }
    }
    return Z;
}