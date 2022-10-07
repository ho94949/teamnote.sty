vector<int> M(const vector<int>& S) {
    int N = S.size();
    vector<int> M(N);
    int L = 0, R = 0;
    for(int i = 0; i < N; i++) {
        if(i < R && i+M[2*L-i] < R) M[i] = M[2*L-i];
        else {
            L = i, R = max(R, i);
            while(R < N && 2*i-R >=0 && S[R] == S[2*i-R]) ++R;
            M[i] = R-i;
        }
    }
    return M;
}