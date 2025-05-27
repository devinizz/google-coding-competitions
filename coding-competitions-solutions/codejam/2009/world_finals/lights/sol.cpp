#include <bits/stdc++.h>
using namespace std;

/* ---------- 常數 ---------- */
const double ROOM_MIN = 0.0;
const double ROOM_MAX = 100.0;
const double TWO_PI   = acos(-1.0) * 2.0;
const double EPS      = 1e-12;
const double INF      = 1e100;

/* ---------- 幾何基本型別 ---------- */
struct Pt {
    double x, y;
    Pt() : x(0), y(0) {}
    Pt(double _x,double _y):x(_x),y(_y){}
    Pt operator+(const Pt& o)const{return {x+o.x,y+o.y};}
    Pt operator-(const Pt& o)const{return {x-o.x,y-o.y};}
    Pt operator*(double k)  const{return {x*k,  y*k  };}   // 右乘常數
};
inline double dot (const Pt& a,const Pt& b){return a.x*b.x + a.y*b.y;}
inline double cross(const Pt& a,const Pt& b){return a.x*b.y - a.y*b.x;}
inline double norm2(const Pt& a){return dot(a,a);}
inline double norm (const Pt& a){return sqrt(norm2(a));}

/* ---------- 柱子資料 ---------- */
struct Pillar{ Pt c; double r; };

/* ---------- Ray 與牆／圓交點 ---------- */
double rayHitWall(const Pt& O,double dx,double dy){
    double t = INF;

    // 垂直牆 x = 0 / 100
    if (fabs(dx) > EPS){
        for (double X : {ROOM_MIN, ROOM_MAX}){
            double tx = (X - O.x) / dx;
            if (tx > EPS){
                double y = O.y + dy * tx;
                if (y >= ROOM_MIN - EPS && y <= ROOM_MAX + EPS)
                    t = min(t, tx);
            }
        }
    }
    // 水平牆 y = 0 / 100
    if (fabs(dy) > EPS){
        for (double Y : {ROOM_MIN, ROOM_MAX}){
            double ty = (Y - O.y) / dy;
            if (ty > EPS){
                double x = O.x + dx * ty;
                if (x >= ROOM_MIN - EPS && x <= ROOM_MAX + EPS)
                    t = min(t, ty);
            }
        }
    }
    return t;
}

double rayHitCircle(const Pt& O,double dx,double dy,
                    const Pt& C,double r){
    double ox = O.x - C.x, oy = O.y - C.y;
    double b  = 2.0 * (ox*dx + oy*dy);            // a==1 (dx^2+dy^2==1)
    double c  = ox*ox + oy*oy - r*r;
    double D  = b*b - 4.0*c;
    if (D < -1e-8) return INF;                    // 明確落在圓外
    D = max(0.0, D);                              // −1e‑8 ~ 0 當成 0
    double sq = sqrt(D);
    double t1 = (-b - sq) * 0.5;
    if (t1 > EPS) return t1;
    double t2 = (-b + sq) * 0.5;
    if (t2 > EPS) return t2;
    return INF;
}

/* ---------- Sutherland–Hodgman (三角形裁切三角形) ---------- */
vector<Pt> clipTri(const vector<Pt>& subj, vector<Pt> clip){
    if (cross(clip[1]-clip[0], clip[2]-clip[0]) < 0)  // 轉 CCW
        reverse(clip.begin(), clip.end());

    vector<Pt> out = subj;

    for (int e=0; e<3 && !out.empty(); ++e){
        Pt A = clip[e], B = clip[(e+1)%3];
        vector<Pt> nxt;

        auto inside = [&](const Pt& P){
            return cross(B-A, P-A) >= -1e-12;
        };

        for (int i=0, n=out.size(); i<n; ++i){
            Pt P = out[i], Q = out[(i+1)%n];
            bool inP = inside(P), inQ = inside(Q);

            if (inP && inQ)                nxt.push_back(Q);
            else if (inP && !inQ){         // 出去
                Pt u = Q-P;
                double denom = cross(B-A, u);
                if (fabs(denom) > EPS){
                    double t = cross(B-A, A-P) / denom;
                    if (t>=0 && t<=1) nxt.push_back(P + u*t);
                }
            }else if (!inP && inQ){        // 進來
                Pt u = Q-P;
                double denom = cross(B-A, u);
                if (fabs(denom) > EPS){
                    double t = cross(B-A, A-P) / denom;
                    if (t>=0 && t<=1) nxt.push_back(P + u*t);
                }
                nxt.push_back(Q);
            }
        }
        out.swap(nxt);
    }
    return out;
}

/* ---------- 多邊形面積 ---------- */
double polyArea(const vector<Pt>& p){
    double s = 0;
    int n = p.size();
    for (int i=0;i<n;i++)  s += cross(p[i], p[(i+1)%n]);
    return fabs(s) * 0.5;
}

/* ---------- 三角形 − 圓交積 (圓心在原點) ---------- */
double triCircle(const Pt& a,const Pt& b,double r){
    /* 依邊切成數段，再對每段判斷在圓內還是外部扇形 */
    auto len2 = [](const Pt& p){ return p.x*p.x + p.y*p.y; };

    Pt A=a, B=b;
    if (fabs(A.x-B.x)<EPS && fabs(A.y-B.y)<EPS) return 0.0;

    bool inA = len2(A) <= r*r + EPS;
    bool inB = len2(B) <= r*r + EPS;
    if (inA && inB)   return cross(A,B)*0.5;      // 整段在圓內

    Pt d = B-A;
    double Acoef = dot(d,d);
    double Bcoef = 2*dot(A,d);
    double Ccoef = dot(A,A) - r*r;
    double D     = Bcoef*Bcoef - 4*Acoef*Ccoef;

    vector<double> ts = {0.0, 1.0};
    if (D >= -1e-8 && Acoef > EPS){
        D = max(0.0, D);
        double sq = sqrt(D);
        double t1 = (-Bcoef - sq) / (2*Acoef);
        double t2 = (-Bcoef + sq) / (2*Acoef);
        if (t1>0 && t1<1) ts.push_back(t1);
        if (t2>0 && t2<1) ts.push_back(t2);
    }
    sort(ts.begin(), ts.end());

    double s = 0, r2 = r*r;
    for (size_t i=0;i+1<ts.size();++i){
        double t0 = ts[i], t1 = ts[i+1], tm = 0.5*(t0+t1);
        Pt  Pm = A + d*tm;
        Pt  P0 = A + d*t0;
        Pt  P1 = A + d*t1;

        if (len2(Pm) <= r2 + EPS)          // 弦在圓內
            s += cross(P0,P1)*0.5;
        else{                              // 圓弓
            double ang = atan2(P1.y,P1.x) - atan2(P0.y,P0.x);
            if (ang <= -M_PI) ang += TWO_PI;
            if (ang >   M_PI) ang -= TWO_PI;
            s += 0.5 * r2 * ang;
        }
    }
    return s;
}

/* ---------- 多邊形 − 圓交積 ---------- */
double polyCircleArea(const vector<Pt>& poly,const Pt& C,double r){
    double s = 0;
    for (size_t i=0;i<poly.size();++i){
        Pt a = {poly[i].x   - C.x, poly[i].y   - C.y};
        Pt b = {poly[(i+1)%poly.size()].x - C.x,
                poly[(i+1)%poly.size()].y - C.y};
        s += triCircle(a,b,r);
    }
    return fabs(s);
}

/* ---------- Wedge 結構 ---------- */
struct Wedge{
    Pt  Pwall1, Pwall2;   // 兩條邊在牆上的終點
    Pt  Q1, Q2;           // 切點 (若與柱相交)
    bool isPillar;
    int  pid;             // 柱索引 (牆則 -1)
};

/* ---------- 產生所有 wedge ---------- */
vector<Wedge> buildWedges(const Pt& O,const vector<Pillar>& pillars){
    vector<double> ang;

    /* 四個房間角落 */
    const Pt corner[4]={{ROOM_MIN,ROOM_MIN},{ROOM_MIN,ROOM_MAX},
                        {ROOM_MAX,ROOM_MIN},{ROOM_MAX,ROOM_MAX}};
    for (auto &p:corner){
        double a=atan2(p.y-O.y, p.x-O.x);
        if (a<0) a+=TWO_PI;
        ang.push_back(a);
    }

    /* 每個柱子的兩條外切線 */
    for (int i=0;i<(int)pillars.size();++i){
        const auto& P = pillars[i];
        Pt v = {P.c.x-O.x, P.c.y-O.y};
        double d = norm(v);
        double base = atan2(v.y,v.x);
        if (base<0) base+=TWO_PI;
        double alpha = asin(min(1.0, P.r/d));
        ang.push_back(fmod(base-alpha+TWO_PI, TWO_PI));
        ang.push_back(fmod(base+alpha+TWO_PI, TWO_PI));
    }

    /* 排序去重 */
    sort(ang.begin(), ang.end());
    vector<double> uniq;
    for (double a:ang)
        if (uniq.empty() || fabs(a-uniq.back())>1e-10) uniq.push_back(a);
    ang.swap(uniq);
    int m = ang.size();

    /* 每條半線先撞牆位置 */
    struct Ray{ double dx,dy; Pt Pw; };
    vector<Ray> R(m);
    for (int i=0;i<m;++i){
        double a = ang[i];
        double dx = cos(a), dy = sin(a);
        double t  = rayHitWall(O,dx,dy);
        R[i]={dx,dy,{O.x+dx*t, O.y+dy*t}};
    }

    vector<Wedge> wlist;
    for (int i=0;i<m;++i){
        int j = (i+1)%m;
        double a1 = ang[i];
        double a2 = ang[j] + (j==0 ? TWO_PI : 0);   // 跨 2π 時補償
        double amid = (a1 + a2)*0.5;
        double dxm  = cos(amid), dym = sin(amid);

        /* 先假設撞牆，再檢查是否柱子更近 */
        double tWall = rayHitWall(O,dxm,dym);
        bool   hitP  = false;
        int    pid   = -1;
        double tMin  = tWall;

        for (int k=0;k<(int)pillars.size();++k){
            double t = rayHitCircle(O,dxm,dym, pillars[k].c, pillars[k].r);
            if (t < tMin - 1e-9){
                hitP=true; pid=k; tMin=t;
            }
        }

        const auto& r1 = R[i];
        const auto& r2 = R[j];

        if (!hitP){                                  // 牆 wedge
            wlist.push_back({r1.Pw, r2.Pw, {}, {}, false,-1});
        }else{                                       // 柱 wedge
            const auto& P = pillars[pid];
            double t1 = rayHitCircle(O,r1.dx,r1.dy,P.c,P.r);
            double t2 = rayHitCircle(O,r2.dx,r2.dy,P.c,P.r);
            Pt Q1 = {O.x + r1.dx*t1, O.y + r1.dy*t1};
            Pt Q2 = {O.x + r2.dx*t2, O.y + r2.dy*t2};
            wlist.push_back({r1.Pw, r2.Pw, Q1,Q2, true,pid});
        }
    }
    return wlist;
}

/* ---------- (準)三角形面積 ---------- */
double wedgeArea(const Pt& O,const Wedge& w,const vector<Pillar>& pillars){
    if (!w.isPillar)          // 普通三角形
        return fabs(cross(w.Pwall1-O, w.Pwall2-O))*0.5;

    const auto& P = pillars[w.pid];
    double tri = fabs(cross(w.Q1-O, w.Q2-O))*0.5;
    Pt v1 = w.Q1-P.c, v2=w.Q2-P.c;
    double ang = fabs(atan2(cross(v1,v2), dot(v1,v2)));
    double segment = 0.5*P.r*P.r*ang - fabs(cross(v1,v2))*0.5;
    return tri - segment;     // 三角形扣掉弓形
}

/* ---------- 取 wedge 對應三角形 (for 裁切) ---------- */
vector<Pt> triOf(const Pt& O,const Wedge& w){
    Pt P1 = w.isPillar ? w.Q1 : w.Pwall1;
    Pt P2 = w.isPillar ? w.Q2 : w.Pwall2;
    if (cross(P1-O,P2-O) < 0) swap(P1,P2);   // 保 CCW
    return {O,P1,P2};
}

#include <iostream>
using namespace std;

void sol() {
        Pt R,G;  cin>>R.x>>R.y>>G.x>>G.y;
        int n;   cin>>n;
        vector<Pillar> pillars(n);
        for (int i=0;i<n;++i)
            cin>>pillars[i].c.x>>pillars[i].c.y>>pillars[i].r;

        /* 建 wedge */
        auto Wr = buildWedges(R, pillars);
        auto Wg = buildWedges(G, pillars);

        /* 個別光源面積 */
        double Ar = 0, Ag = 0;
        for (auto &w:Wr) Ar += wedgeArea(R,w,pillars);
        for (auto &w:Wg) Ag += wedgeArea(G,w,pillars);

        /* 黃色 (交集) */
        double Ay = 0;
        for (const auto &wr : Wr){
            auto Tr = triOf(R, wr);
            for (const auto &wg : Wg){
                auto Tg = triOf(G, wg);
                auto poly = clipTri(Tr, Tg);
                if (poly.empty()) continue;

                double area = polyArea(poly);

                if (wr.isPillar){
                    const auto& P = pillars[wr.pid];
                    area -= polyCircleArea(poly, P.c, P.r);
                }
                if (wg.isPillar &&
                    (!wr.isPillar || wg.pid != wr.pid)){
                    const auto& P = pillars[wg.pid];
                    area -= polyCircleArea(poly, P.c, P.r);
                }
                if (area > 1e-10) Ay += area;
            }
        }

        double AonlyR = Ar - Ay;
        double AonlyG = Ag - Ay;

        /* 房間有效面積 (扣掉柱子本身) */
        double room = 10000.0;
        for (auto &p:pillars) room -= M_PI * p.r * p.r;

        double Ablack = room - (AonlyR + AonlyG + Ay);

        /* 輸出 */
        cout<<Ablack<<"\n"<<AonlyR<<"\n"<<AonlyG<<"\n"<<Ay<<"\n";
}

int main() {
  int T; cin >> T;
  for (int case_num = 1; case_num <= T; case_num++) {
    cout << "Case #" << case_num << ":\n";

    sol();
  }
  return 0;
}
