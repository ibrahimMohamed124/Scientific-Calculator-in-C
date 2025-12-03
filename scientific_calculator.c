#include <gtk/gtk.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// Global variables
GtkWidget *display;
GtkWidget *window;
GtkWidget *basic_grid;
GtkWidget *scientific_grid;
GtkWidget *notebook;
GtkWidget *switch_button;
GtkWidget *rad_deg_button;

char current_input[50] = "0";
double memory = 0.0;
int is_result_displayed = 0;
int is_radians = 1; // 1 for radians, 0 for degrees
double last_result = 0.0;
int current_page = 0; // 0 for basic, 1 for scientific

// Function prototypes
void update_display();
void append_to_input(const char *text);
void clear_input();
void calculate_result();
void handle_button_click(GtkWidget *widget, gpointer data);
void create_calculator();
void switch_page();
void create_basic_page();
void create_scientific_page();
void toggle_rad_deg();

// Update the display widget
void update_display() {
    gtk_label_set_text(GTK_LABEL(display), current_input);
}

// Append text to current input
void append_to_input(const char *text) {
    if (is_result_displayed) {
        strcpy(current_input, "0");
        is_result_displayed = 0;
    }
    
    if (strcmp(current_input, "0") == 0 && strcmp(text, ".") != 0) {
        strcpy(current_input, text);
    } else {
        strcat(current_input, text);
    }
    
    update_display();
}

// Clear the input
void clear_input() {
    strcpy(current_input, "0");
    update_display();
    is_result_displayed = 0;
}

// Clear everything
void clear_all() {
    strcpy(current_input, "0");
    memory = 0.0;
    last_result = 0.0;
    update_display();
    is_result_displayed = 0;
}

// Toggle between radians and degrees
void toggle_rad_deg() {
    is_radians = !is_radians;
    if (is_radians) {
        gtk_button_set_label(GTK_BUTTON(rad_deg_button), "Rad");
    } else {
        gtk_button_set_label(GTK_BUTTON(rad_deg_button), "Deg");
    }
}

// Calculate the result
void calculate_result() {
    // Simple expression evaluation
    char expression[100];
    strcpy(expression, current_input);
    
    double result = 0.0;
    double a, b;
    char op;
    
    if (sscanf(expression, "%lf %c %lf", &a, &op, &b) == 3) {
        switch(op) {
            case '+': result = a + b; break;
            case '-': result = a - b; break;
            case '*': result = a * b; break;
            case 'x': result = a * b; break;
            case '/': 
                if (b != 0) {
                    result = a / b;
                } else {
                    strcpy(current_input, "Error");
                    update_display();
                    is_result_displayed = 1;
                    return;
                }
                break;
            case '^': result = pow(a, b); break;
            case '%': result = fmod(a, b); break;
        }
        
        last_result = result;
        sprintf(current_input, "%.10g", result);
        update_display();
        is_result_displayed = 1;
    } else {
        // Try to parse single number
        double value;
        if (sscanf(expression, "%lf", &value) == 1) {
            last_result = value;
            sprintf(current_input, "%.10g", value);
            update_display();
            is_result_displayed = 1;
        }
    }
}

// Switch between basic and scientific pages
void switch_page() {
    if (current_page == 0) {
        // Switch to scientific
        gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook), 1);
        gtk_button_set_label(GTK_BUTTON(switch_button), "Basic Mode");
        current_page = 1;
    } else {
        // Switch to basic
        gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook), 0);
        gtk_button_set_label(GTK_BUTTON(switch_button), "Scientific Mode");
        current_page = 0;
    }
}

// Handle button clicks
void handle_button_click(GtkWidget *widget, gpointer data) {
    const char *label = gtk_button_get_label(GTK_BUTTON(widget));
    
    if (strcmp(label, "C") == 0) {
        clear_all();
    } else if (strcmp(label, "CE") == 0) {
        clear_input();
    } else if (strcmp(label, "=") == 0) {
        calculate_result();
    } else if (strcmp(label, "⌫") == 0) {
        // Backspace
        int len = strlen(current_input);
        if (len > 1) {
            current_input[len - 1] = '\0';
        } else {
            strcpy(current_input, "0");
        }
        update_display();
        is_result_displayed = 0;
    } else if (strcmp(label, "π") == 0) {
        sprintf(current_input, "%.10g", M_PI);
        update_display();
        is_result_displayed = 1;
    } else if (strcmp(label, "e") == 0) {
        sprintf(current_input, "%.10g", M_E);
        update_display();
        is_result_displayed = 1;
    } else if (strcmp(label, "x²") == 0) {
        double value = atof(current_input);
        last_result = value * value;
        sprintf(current_input, "%.10g", last_result);
        update_display();
        is_result_displayed = 1;
    } else if (strcmp(label, "√") == 0) {
        double value = atof(current_input);
        if (value >= 0) {
            last_result = sqrt(value);
            sprintf(current_input, "%.10g", last_result);
        } else {
            strcpy(current_input, "Error");
        }
        update_display();
        is_result_displayed = 1;
    } else if (strcmp(label, "sin") == 0) {
        double value = atof(current_input);
        if (!is_radians) {
            value = value * M_PI / 180.0;
        }
        last_result = sin(value);
        sprintf(current_input, "%.10g", last_result);
        update_display();
        is_result_displayed = 1;
    } else if (strcmp(label, "cos") == 0) {
        double value = atof(current_input);
        if (!is_radians) {
            value = value * M_PI / 180.0;
        }
        last_result = cos(value);
        sprintf(current_input, "%.10g", last_result);
        update_display();
        is_result_displayed = 1;
    } else if (strcmp(label, "tan") == 0) {
        double value = atof(current_input);
        if (!is_radians) {
            value = value * M_PI / 180.0;
        }
        last_result = tan(value);
        sprintf(current_input, "%.10g", last_result);
        update_display();
        is_result_displayed = 1;
    } else if (strcmp(label, "log") == 0) {
        double value = atof(current_input);
        if (value > 0) {
            last_result = log10(value);
            sprintf(current_input, "%.10g", last_result);
        } else {
            strcpy(current_input, "Error");
        }
        update_display();
        is_result_displayed = 1;
    } else if (strcmp(label, "ln") == 0) {
        double value = atof(current_input);
        if (value > 0) {
            last_result = log(value);
            sprintf(current_input, "%.10g", last_result);
        } else {
            strcpy(current_input, "Error");
        }
        update_display();
        is_result_displayed = 1;
    } else if (strcmp(label, "x!") == 0) {
        int n = atoi(current_input);
        if (n >= 0 && n <= 20) {
            long long fact = 1;
            for (int i = 1; i <= n; i++) {
                fact *= i;
            }
            last_result = (double)fact;
            sprintf(current_input, "%.10g", last_result);
        } else {
            strcpy(current_input, "Error");
        }
        update_display();
        is_result_displayed = 1;
    } else if (strcmp(label, "M+") == 0) {
        memory += atof(current_input);
    } else if (strcmp(label, "M-") == 0) {
        memory -= atof(current_input);
    } else if (strcmp(label, "MR") == 0) {
        sprintf(current_input, "%.10g", memory);
        update_display();
        is_result_displayed = 1;
    } else if (strcmp(label, "MC") == 0) {
        memory = 0.0;
    } else if (strcmp(label, "±") == 0) {
        double value = atof(current_input);
        value = -value;
        sprintf(current_input, "%.10g", value);
        update_display();
    } else if (strcmp(label, "1/x") == 0) {
        double value = atof(current_input);
        if (value != 0) {
            last_result = 1.0 / value;
            sprintf(current_input, "%.10g", last_result);
        } else {
            strcpy(current_input, "Error");
        }
        update_display();
        is_result_displayed = 1;
    } else if (strcmp(label, "|x|") == 0) {
        double value = atof(current_input);
        last_result = fabs(value);
        sprintf(current_input, "%.10g", last_result);
        update_display();
        is_result_displayed = 1;
    } else if (strcmp(label, "10^x") == 0) {
        double value = atof(current_input);
        last_result = pow(10, value);
        sprintf(current_input, "%.10g", last_result);
        update_display();
        is_result_displayed = 1;
    } else if (strcmp(label, "e^x") == 0) {
        double value = atof(current_input);
        last_result = exp(value);
        sprintf(current_input, "%.10g", last_result);
        update_display();
        is_result_displayed = 1;
    } else if (strcmp(label, "x^y") == 0) {
        append_to_input("^");
    } else if (strcmp(label, "(") == 0) {
        append_to_input("(");
    } else if (strcmp(label, ")") == 0) {
        append_to_input(")");
    } else if (strcmp(label, "%") == 0) {
        // Handle percentage
        double value = atof(current_input);
        last_result = value / 100.0;
        sprintf(current_input, "%.10g", last_result);
        update_display();
        is_result_displayed = 1;
    } else {
        // For all other buttons, just append to input
        append_to_input(label);
    }
}

// Create a button with styling
GtkWidget* create_calc_button(const char *label, const char *css_class, int width, int height) {
    GtkWidget *button = gtk_button_new_with_label(label);
    
    // Apply CSS styling
    GtkStyleContext *context = gtk_widget_get_style_context(button);
    gtk_style_context_add_class(context, "calc-button");
    if (css_class) {
        gtk_style_context_add_class(context, css_class);
    }
    
    g_signal_connect(button, "clicked", G_CALLBACK(handle_button_click), NULL);
    
    // Set button size
    gtk_widget_set_size_request(button, width, height);
    
    return button;
}

// Create basic calculator page
void create_basic_page() {
    basic_grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(basic_grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(basic_grid), 5);
    gtk_grid_set_row_homogeneous(GTK_GRID(basic_grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(basic_grid), TRUE);
    
    // Basic calculator buttons layout - 5x4 grid
    const char *basic_buttons[5][4] = {
        {"C", "CE", "⌫", "/"},
        {"7", "8", "9", "x"},
        {"4", "5", "6", "-"},
        {"1", "2", "3", "+"},
        {"0", ".", "=", "%"}
    };
    
    // Create and place basic calculator buttons
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 4; col++) {
            const char *label = basic_buttons[row][col];
            const char *css_class = NULL;
            
            // Assign CSS classes based on button type
            if (strcmp(label, "=") == 0) {
                css_class = "equals";
            } else if (strcmp(label, "C") == 0 || strcmp(label, "CE") == 0 || strcmp(label, "⌫") == 0) {
                css_class = "clear";
            } else if (strcmp(label, "+") == 0 || strcmp(label, "-") == 0 || 
                      strcmp(label, "x") == 0 || strcmp(label, "/") == 0 ||
                      strcmp(label, "%") == 0) {
                css_class = "operator";
            } else if (strchr("0123456789.", label[0]) != NULL) {
                css_class = "number";
            }
            
            GtkWidget *button = create_calc_button(label, css_class, 70, 60);
            gtk_grid_attach(GTK_GRID(basic_grid), button, col, row, 1, 1);
        }
    }
}

// Create scientific calculator page
void create_scientific_page() {
    scientific_grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(scientific_grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(scientific_grid), 5);
    gtk_grid_set_row_homogeneous(GTK_GRID(scientific_grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(scientific_grid), TRUE);
    
    // Scientific calculator buttons layout - 7x5 grid (more compact)
    const char *sci_buttons[7][5] = {
        {"sin", "cos", "tan", "log", "ln"},
        {"x²", "√", "x^y", "10^x", "e^x"},
        {"(", ")", "x!", "|x|", "1/x"},
        {"7", "8", "9", "/", "M+"},
        {"4", "5", "6", "x", "M-"},
        {"1", "2", "3", "-", "MR"},
        {"0", ".", "=", "+", "MC"}
    };
    
    // Create and place scientific calculator buttons
    for (int row = 0; row < 7; row++) {
        for (int col = 0; col < 5; col++) {
            const char *label = sci_buttons[row][col];
            const char *css_class = NULL;
            
            // Assign CSS classes based on button type
            if (strcmp(label, "=") == 0) {
                css_class = "equals";
            } else if (strcmp(label, "M+") == 0 || strcmp(label, "M-") == 0 || 
                      strcmp(label, "MR") == 0 || strcmp(label, "MC") == 0) {
                css_class = "memory";
            } else if (strcmp(label, "+") == 0 || strcmp(label, "-") == 0 || 
                      strcmp(label, "x") == 0 || strcmp(label, "/") == 0) {
                css_class = "operator";
            } else if (strchr("0123456789.", label[0]) != NULL) {
                css_class = "number";
            } else {
                css_class = "function";
            }
            
            GtkWidget *button = create_calc_button(label, css_class, 65, 55);
            gtk_grid_attach(GTK_GRID(scientific_grid), button, col, row, 1, 1);
        }
    }
}

//============================ Create the calculator UI ============================
void create_calculator() {
    // Create main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Scientific Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 600); // أصغر حجم
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    
    // Connect the destroy signal
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // Create main container
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), main_box);
    gtk_container_set_border_width(GTK_CONTAINER(main_box), 10);
    
    // Create header box for display and controls
    GtkWidget *header_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(main_box), header_box, FALSE, FALSE, 0);
    
    // Create display
    GtkWidget *display_frame = gtk_frame_new(NULL);
    gtk_frame_set_shadow_type(GTK_FRAME(display_frame), GTK_SHADOW_IN);
    
    display = gtk_label_new("0");
    gtk_label_set_xalign(GTK_LABEL(display), 1.0); // Right align
    gtk_label_set_yalign(GTK_LABEL(display), 0.5);
    gtk_widget_set_name(display, "display");
    gtk_widget_set_size_request(display, 380, 80);
    
    gtk_container_add(GTK_CONTAINER(display_frame), display);
    gtk_box_pack_start(GTK_BOX(header_box), display_frame, FALSE, FALSE, 0);
    
    // Create control buttons box
    GtkWidget *control_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(header_box), control_box, FALSE, FALSE, 5);
    
    // Create special buttons
    GtkWidget *pi_button = create_calc_button("π", "constant", 50, 35);
    GtkWidget *e_button = create_calc_button("e", "constant", 50, 35);
    rad_deg_button = create_calc_button("Rad", "constant", 60, 35);
    g_signal_connect(rad_deg_button, "clicked", G_CALLBACK(toggle_rad_deg), NULL);
    
    GtkWidget *sign_button = create_calc_button("±", "function", 50, 35);
    
    // Mode switch button
    switch_button = gtk_button_new_with_label("Scientific Mode");
    gtk_widget_set_size_request(switch_button, 120, 35);
    g_signal_connect(switch_button, "clicked", G_CALLBACK(switch_page), NULL);
    GtkStyleContext *switch_context = gtk_widget_get_style_context(switch_button);
    gtk_style_context_add_class(switch_context, "switch-button");
    
    // Pack control buttons
    gtk_box_pack_start(GTK_BOX(control_box), pi_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(control_box), e_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(control_box), rad_deg_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(control_box), sign_button, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(control_box), switch_button, FALSE, FALSE, 0);
    
    // Create notebook (tab container) for pages
    notebook = gtk_notebook_new();
    gtk_notebook_set_show_tabs(GTK_NOTEBOOK(notebook), FALSE);
    gtk_notebook_set_show_border(GTK_NOTEBOOK(notebook), FALSE);
    gtk_box_pack_start(GTK_BOX(main_box), notebook, TRUE, TRUE, 10);
    
    // Create pages
    create_basic_page();
    create_scientific_page();
    
    // Create containers for each page
    GtkWidget *basic_page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *scientific_page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    
    // Add title labels with subtle styling
    GtkWidget *basic_label = gtk_label_new("Basic Calculator");
    GtkWidget *scientific_label = gtk_label_new("Scientific Calculator");
    
    GtkStyleContext *basic_label_context = gtk_widget_get_style_context(basic_label);
    GtkStyleContext *sci_label_context = gtk_widget_get_style_context(scientific_label);
    gtk_style_context_add_class(basic_label_context, "page-label");
    gtk_style_context_add_class(sci_label_context, "page-label");
    
    gtk_box_pack_start(GTK_BOX(basic_page), basic_label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(basic_page), basic_grid, TRUE, TRUE, 5);
    
    gtk_box_pack_start(GTK_BOX(scientific_page), scientific_label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(scientific_page), scientific_grid, TRUE, TRUE, 5);
    
    // Add pages to notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), basic_page, NULL);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), scientific_page, NULL);
    
    // Set initial page
    gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook), 0);
    
    // Create status bar
    GtkWidget *status_bar = gtk_statusbar_new();
    gtk_statusbar_push(GTK_STATUSBAR(status_bar), 0, 
                      "Ready - Use buttons above to switch modes");
    gtk_box_pack_start(GTK_BOX(main_box), status_bar, FALSE, FALSE, 0);
    
    // Load CSS
    GtkCssProvider *css_provider = gtk_css_provider_new();
    const char *css_data = 
        /* GLOBAL WINDOW */
"window {"
"    background: linear-gradient(145deg, #0f0f0f, #1a1a1a);"
"}"

/* DISPLAY */
"#display {"
"    color: #ffffff;"
"    font-size: 30px;"
"    padding: 12px;"
"    background: linear-gradient(180deg, #1c1c1c, #111111);"
"    border-radius: 10px;"
"    box-shadow: 0 0 12px rgba(0,0,0,0.6);"
"    border: 1px solid #333;"
"}"

/* BASE BUTTON */
"button.calc-button {"
"    background: linear-gradient(180deg, #2a2a2a, #1d1d1d);"
"    color: #ffffff;"
"    border-radius: 10px;"
"    font-size: 18px;"
"    padding: 10px;"
"    border: 1px solid #444;"
"    box-shadow: 0 4px 10px rgba(0,0,0,0.4);"
"    transition: 150ms;"
"}"
"button.calc-button:hover {"
"    background: linear-gradient(180deg, #3a3a3a, #2a2a2a);"
"    box-shadow: 0 6px 12px rgba(0,0,0,0.6);"
"}"

/* NUMBER BUTTONS */
"button.number {"
"    background: linear-gradient(180deg, #333, #222);"
"}"
"button.number:hover {"
"    background: linear-gradient(180deg, #444, #292929);"
"}"

/* OPERATOR BUTTONS */
"button.operator {"
"    background: linear-gradient(180deg, #375a7f, #2c4057);"
"    border: 1px solid #4f7eb0;"
"}"
"button.operator:hover {"
"    background: linear-gradient(180deg, #46759b, #34506f);"
"}"

/* FUNCTION BUTTONS */
"button.function {"
"    background: linear-gradient(180deg, #5a3ea6, #472f85);"
"    border: 1px solid #7c55d1;"
"}"
"button.function:hover {"
"    background: linear-gradient(180deg, #6e4bc4, #54339c);"
"}"

/* MEMORY BUTTONS */
"button.memory {"
"    background: linear-gradient(180deg, #6e3939, #542f2f);"
"    border: 1px solid #a44747;"
"}"
"button.memory:hover {"
"    background: linear-gradient(180deg, #8b4646, #643a3a);"
"}"

/* CLEAR BUTTON */
"button.clear {"
"    background: linear-gradient(180deg, #b83232, #8a2626);"
"    border: 1px solid #d44c4c;"
"}"
"button.clear:hover {"
"    background: linear-gradient(180deg, #d13b3b, #a22e2e);"
"}"

/* EQUALS BTN */
"button.equals {"
"    background: linear-gradient(180deg, #0f9c34, #0a6d27);"
"    border: 1px solid #14c241;"
"    box-shadow: 0 0 12px rgba(0,255,100,0.25);"
"}"
"button.equals:hover {"
"    background: linear-gradient(180deg, #12b63e, #0d7d2e);"
"    box-shadow: 0 0 16px rgba(0,255,120,0.4);"
"}"

/* CONSTANT BUTTONS */
"button.constant {"
"    background: linear-gradient(180deg, #3a5d3a, #2c442c);"
"    border: 1px solid #4e7a4e;"
"}"
"button.constant:hover {"
"    background: linear-gradient(180deg, #4a7a4a, #365a36);"
"}"
;
    
    gtk_css_provider_load_from_data(css_provider, css_data, -1, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                             GTK_STYLE_PROVIDER(css_provider),
                                             GTK_STYLE_PROVIDER_PRIORITY_USER);
    
    // Show all widgets
    gtk_widget_show_all(window);
}

// Main function
int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    
    create_calculator();
    
    gtk_main();
    
    return 0;
}