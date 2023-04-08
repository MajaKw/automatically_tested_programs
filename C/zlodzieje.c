#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {

    int z, i;
    double x, y, c, c1, c2, w, b, e, x2, y2, xw, yw;

    scanf("%d", &z);
    for (i = 0; i < z; ++i) {

        scanf("%lf %lf %lf", &x, &y, &c);

        if (x > y) {
            e = y;
        }
        else e = x;
        b = 0;
        x2 = x * x;
        y2 = y * y;
        do {
            w = (b + e) / 2;
            xw = sqrt(x2 - w * w);
            yw = sqrt(y2 - w * w);
            c2 = xw * yw;
            c1 = (xw + yw) * c;
            // c' >= c
            if (c2 >= c1) {
                b = w;
            }
            else {

                // c' < c
                e = w;

            }
        } while (fabs(c2 - c1) > 0.001);
        printf("%.3lf\n", w);

    }


    return 0;
}