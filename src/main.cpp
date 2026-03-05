#include <iostream>
#include <vector>
#include <cmath>
#include <ncurses.h>
#include <pulse/simple.h>
#include <pulse/error.h>
#include <fftw3.h>
#include <algorithm>
#include <unistd.h>
#include <locale.h>

struct Config {
    int numBars = 32;
    float gain = 0.8f;        // Adjust this if bars are too high/low
    float fallSpeed = 0.5f;   // Smoothness of the drop
};

std::string getMonitorDevice() {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen("pactl get-default-sink 2>/dev/null", "r");
    if (!pipe) return "";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) result += buffer;
    pclose(pipe);
    if (!result.empty() && result.back() == '\n') result.pop_back();
    return result + ".monitor";
}

int main() {
    setlocale(LC_ALL, ""); // Force UTF-8 support for solid blocks
    Config cfg;
    
    std::string monitor = getMonitorDevice();
    static const pa_sample_spec ss = {.format = PA_SAMPLE_FLOAT32LE, .rate = 44100, .channels = 2};
    pa_simple *s = pa_simple_new(NULL, "ASVP", PA_STREAM_RECORD, monitor.c_str(), "Record", &ss, NULL, NULL, NULL);

    const int n = 1024; 
    double *in = (double*) fftw_malloc(sizeof(double) * n);
    fftw_complex *out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n);
    fftw_plan p = fftw_plan_dft_r2c_1d(n, in, out, FFTW_ESTIMATE);

    initscr(); noecho(); curs_set(0); timeout(1); start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);

    std::vector<float> audioBuffer(n * 2);
    std::vector<float> smoothHeights(cfg.numBars, 0.0f);

    while (true) {
        if (getch() == 'q') break;
        if (is_term_resized(LINES, COLS)) { resizeterm(LINES, COLS); clear(); }

        pa_simple_read(s, audioBuffer.data(), audioBuffer.size() * sizeof(float), NULL);

        for (int i = 0; i < n; i++) {
            in[i] = (audioBuffer[i*2] + audioBuffer[i*2+1]) / 2.0;
        }

        fftw_execute(p);
        erase();

        // Dynamically calculate bar width to fill the screen
        float barSpace = (float)COLS / cfg.numBars;

        for (int i = 0; i < cfg.numBars; i++) {
            // SKIP BINS 0-2: This removes the "static" bar on the far left
            // We spread the 32 bars across the most active 120 bins
            int startBin = (i * 3) + 3; 
            double mag = 0;
            for(int j=0; j<3; j++) {
                mag += std::sqrt(out[startBin+j][0]*out[startBin+j][0] + out[startBin+j][1]*out[startBin+j][1]);
            }
            mag /= 3.0;

            // Logarithmic jump with a slight boost for treble
            float targetHeight = std::log10(mag + 1.0f) * (LINES * cfg.gain) * (1.0f + i*0.02f);

            if (targetHeight > smoothHeights[i]) smoothHeights[i] = targetHeight;
            else smoothHeights[i] -= cfg.fallSpeed;
            if (smoothHeights[i] < 0) smoothHeights[i] = 0;

            int drawHeight = std::min((int)smoothHeights[i], LINES);

            attron(COLOR_PAIR(1));
            int xStart = (int)(i * barSpace);
            int xEnd = (int)((i + 1) * barSpace) - 1; // 1-char gap between towers

            for (int y = 0; y < drawHeight; y++) {
                for (int x = xStart; x < xEnd; x++) {
                    // Universal Solid Block
                    mvaddstr(LINES - y - 1, x, "█");
                }
            }
            attroff(COLOR_PAIR(1));
        }
        refresh();
        usleep(10000); 
    }

    endwin();
    fftw_destroy_plan(p);
    fftw_free(in); fftw_free(out);
    pa_simple_free(s);
    return 0;
}