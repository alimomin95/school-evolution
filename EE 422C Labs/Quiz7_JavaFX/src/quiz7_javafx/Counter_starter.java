/*
 * EE 422C Fall 2016, Quiz 7
 * Name: Ali Ziyaan Momin
 * UT EID: AZM259
 * Unique: 16470
 */

/*
 * Quiz7 grade: 100/100.
 */
package quiz7_javafx;




import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.*;
import javafx.stage.Stage;

import javax.swing.*;

public class Counter_starter extends Application {

    // TODO Field here to hold counter value
    Button butt;
    int count = 0;

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {

        primaryStage.setTitle("100");
        Label l1 = new Label(Integer.toString(count));

        butt = new Button("Counter");
        GridPane layout = new GridPane();
        layout.getColumnConstraints().add(new ColumnConstraints(100));
        layout.getRowConstraints().add(new RowConstraints(100));
        layout.add(l1, 2, 0);
        layout.add(butt, 2, 1);

        butt.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                count++;
                l1.setText(Integer.toString(count));
                System.out.println(count);
            }
        });

        Scene sc = new Scene(layout, 300, 250);
        primaryStage.setScene(sc);
        primaryStage.show();
    }


}