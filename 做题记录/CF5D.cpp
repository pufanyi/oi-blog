#include <cmath>
#include <cstdio>

int main()
{
    double a, vm, L, d, lim, ans = 0;
    scanf("%lf%lf%lf%lf%lf", &a, &vm, &L, &d, &lim);
    double T_to_vm = vm / a, T_to_lim = lim / a;
    double D_to_vm = T_to_vm * (vm / 2.), D_to_lim = T_to_lim * (lim / 2.);
    if (vm > lim && D_to_lim < d)
    {
        double V_maxx = sqrt(lim * lim + a * (d - D_to_lim));
        if (V_maxx > vm)
        {
            double T_jiasu_pj = (V_maxx - vm) / a;
            double D_jiasu_pj = T_jiasu_pj * (V_maxx + vm);
            ans += D_jiasu_pj / vm;
            ans -= D_jiasu_pj / ((V_maxx + vm) / 2.);
        }
        double V_pj = (lim + V_maxx) / 2.;
        ans += (d - D_to_lim) / V_pj;
        L -= d - D_to_lim;
    }
    if (D_to_vm >= L)
        ans += sqrt(2. * L / a);
    else
    {
        ans += T_to_vm;
        L -= D_to_vm;
        ans += L / vm;
    }
    printf("%.12f", ans);
    return 0;
}
