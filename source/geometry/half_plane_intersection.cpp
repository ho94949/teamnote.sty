int get_hp(HalfPlane a) {
    return !(a.B > EPS ||(fabs(a.B) < EPS && a.A > EPS));
}

bool hp_comp(HalfPlane a , HalfPlane b) {
    int hp_a = get_hp(a);
    int hp_b = get_hp(b);
    if(hp_a != hp_b) return hp_a < hp_b;
    if(fabs(a.A * b.B - a.B * b.A) < EPS)
        return a.C < b.C;
    return a.A * b.B - a.B * b.A > EPS;
}

inline bool parallel(HalfPlane a , HalfPlane b) {
    return fabs(a.A - b.A) < EPS && fabs(a.B - b.B) < EPS;
}

bool need_to_pop(vector < HalfPlane > &st , HalfPlane h3) {
    if(st.size() < 2u) return false;
    HalfPlane h1 = * prev(st.end() , 2);
    HalfPlane h2 = * prev(st.end());
    Point p = h3 ^ h2;
    if(! h1.good(p)) return true;
    return false;
}

bool check_emptiness(vector < HalfPlane > & hp) {
    vector < Point > pt;
    for(int i = 0; i <(int) hp.size(); ++ i) {
        int j =(i + 1) % hp.size();
        pt.pb(hp[i]^ hp[j]);
    }
    Point mass_center(0 , 0);
    for(int i = 0; i <(int) pt.size(); ++ i) {
        mass_center += pt[i]/ pt.size();
    }
    for(int i = 0; i <(int) hp.size(); ++ i) {
        if(! hp[i].good(mass_center)) return true;
    }
    return false;
}

vector < HalfPlane > half_planes_intesection(vector < HalfPlane > hp) {
    sort(hp.begin() , hp.end() , hp_comp);
    int sz = 0;
    for(int i = 0; i <(int) hp.size(); ++ i) {
        int j = i;
        while(j <(int) hp.size() && parallel(hp[i], hp[j])) ++ j;
        hp[sz ++]= hp[i];
        i = j - 1;
    }
    hp.resize(sz);
    vector < HalfPlane > st;
    for(int i = 0; i < 2 *(int) hp.size(); ++ i) {
        while(need_to_pop(st , hp[i % hp.size()])) {
            st.pop_back();
        } 
        st.pb(hp[i]);
    }
    vector <int > was(n + 4, -1);
    for(int i = 0; i <(int) st.size(); ++ i) {
        if(was[st[i].id] != -1) {
            vector < HalfPlane > res;
            res.assign(st.begin() + was[st[i].id], st.begin() + i);
            if(check_emptiness(res)) return {};
            return res;
        }
        was[st[i].id] = i;
    }
    return {};
}
