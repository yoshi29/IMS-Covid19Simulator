#include "app_window.h"

// Global variables
static int area_limit;
static GtkWidget *drawing_area;
static cairo_surface_t *surface = NULL;
static int current_width;
static int current_height;


static void close_window()
{
    exit(EXIT_SUCCESS);
}

static void clear_surface()
{
    cairo_t *cr = cairo_create(surface);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);

    cairo_destroy(cr);
}

// Update width and height on window resize
static gboolean configure_event(GtkWidget *widget, GdkEventConfigure *event, gpointer data)
{
    (void)event;
    (void)data;

    if (surface != NULL)
    {
        cairo_surface_destroy(surface);
    }

    current_width = gtk_widget_get_allocated_width(widget);
    current_height = gtk_widget_get_allocated_height(widget);

    surface = gdk_window_create_similar_surface(gtk_widget_get_window(widget), CAIRO_CONTENT_COLOR, current_width, current_height);

    clear_surface();

    return TRUE;
}

static gboolean draw(GtkWidget *widget, cairo_t *cr, gpointer data)
{
    (void)widget;
    (void)data;

    cairo_set_source_surface(cr, surface, 0, 0);
    cairo_paint(cr);

    return FALSE;
}

void draw_person(cairo_t *cr, GtkWidget *widget, Person *p)
{
    (void)widget;

    double x = (double)(p->currentX * current_width / area_limit);
    double y = (double)(p->currentY * current_height / area_limit);

    switch (p->infectionState)
    {
    case NOT_INFECTED:
        cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 0.5);
        break;
    case INFECTED:
        cairo_set_source_rgba(cr, 0.0, 0.7, 0.0, 0.7);
        break;
    case IN_HOSPITAL:
        cairo_set_source_rgba(cr, 0.5, 0.0, 0.5, 0.5);
        break;
    case IMMUNE:
        cairo_set_source_rgba(cr, 0.0, 0.0, 1.0, 0.8);
        break;
    case DEAD:
        cairo_set_source_rgba(cr, 1.0, 0.0, 0.0, 1.0);
        break;
    }

    cairo_arc(cr, x, y, 3, 0, 2 * M_PI);
    cairo_fill(cr);
}


void refresh_window(std::vector<Person *> *people)
{
    clear_surface();

    cairo_t *cr = cairo_create(surface);

    for (auto person : *people)
    {
        draw_person(cr, drawing_area, person);
    }

    cairo_destroy(cr);

    // Invalidate
    gtk_widget_queue_draw_area(drawing_area, 0, 0, current_width, current_height);

    while (gtk_events_pending())
    {
        gtk_main_iteration();
    }
}

static void activate(GtkApplication *application, gpointer data)
{
    // Get simulator function
    simulator_func_t simulator_main = (simulator_func_t)data;

    // Create window
    GtkWidget *window = gtk_application_window_new(application);

    // Set title
    gtk_window_set_title(GTK_WINDOW(window), "IMS - Covid Simulator");

    // Set close function
    g_signal_connect(window, "destroy", G_CALLBACK(close_window), NULL);

    // Create frame
    GtkWidget *frame = gtk_frame_new(NULL);
    gtk_container_add(GTK_CONTAINER(window), frame);

    // Create drawing area
    drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, WINDOW_WIDTH, WINDOW_HEIGHT);
    gtk_container_add(GTK_CONTAINER(frame), drawing_area);

    g_signal_connect(drawing_area, "draw", G_CALLBACK(draw), NULL);

    g_signal_connect(drawing_area, "configure-event", G_CALLBACK(configure_event), NULL);


    gtk_widget_show_all(window);
    clear_surface();

    // Call the simulator
    simulator_main();
}

int open_window(simulator_func_t simulator_func, int area_size)
{
    area_limit = area_size;
    current_width = WINDOW_WIDTH;
    current_height = WINDOW_HEIGHT;

    GtkApplication *application = gtk_application_new("covid.simulator", G_APPLICATION_FLAGS_NONE);

    g_signal_connect(application, "activate", G_CALLBACK(activate), (gpointer)simulator_func);

    int result = g_application_run(G_APPLICATION(application), FALSE, NULL);

    g_object_unref(application);

    return result;
}
