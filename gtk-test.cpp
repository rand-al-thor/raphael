#include <gtk/gtk.h>

static void print_hello( GtkWidget *window,
						 gpointer data )	{
	g_print("Hello world\n");
}

static gboolean on_delete_event( GtkWidget *window,
								 GdkEvent *event,
								 gpointer data )	{
	g_print("delete event occured\n");
}


int main (int argc, char *argv[] )	{
	GtkWidget *window;
	GtkWidget *button;

	// Initialize the gtk library
	gtk_init( &argc, &argv);
	
	// create a new window
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title( GTK_WINDOW(window), "Window");

	// Connect the signals
	g_signal_connect( window, "delete-event", G_CALLBACK(on_delete_event), NULL);
	g_signal_connect( window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	// set border width of the window
	gtk_container_set_border_width( GTK_CONTAINER(window), 10);

	// creates a button with the label "hello world"
	button = gtk_button_new_with_label("Hello world");

	g_signal_connect( button, "clicked", G_CALLBACK(print_hello), NULL);
	g_signal_connect_swapped( button, "clicked", G_CALLBACK(gtk_widget_destroy), window);

	gtk_container_add( GTK_CONTAINER(window), button);
	
	// Show the window and the button
	gtk_widget_show(button);
	gtk_widget_show(window);

	gtk_main();
	
	return 0;
}
