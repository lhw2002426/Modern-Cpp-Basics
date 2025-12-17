#include<bits/stdc++.h>
#include<numbers>

constexpr long double operator"" _ToRad(long double deg) {
    return deg * std::numbers::pi_v<long double> / 180.0;
}

int main() {
    using namespace std;

    long double angle_deg = 90.0;
    long double angle_rad = 90.0_ToRad;

    cout << fixed << setprecision(10);
    cout << "Angle in degrees: " << angle_deg << "°\n";
    cout << "Angle in radians: " << angle_rad << " rad\n";
    cout << 45.0_ToRad << " rad\n";

    return 0;
}