package javafx;

import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.stage.Stage;

/**
 * Created by aliziyaan on 11/4/16.
 */
public class FX extends Application{
    public static void main(String[] args){
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws Exception {
        /*
        StackPane root = new StackPane();
        Circle cir = new Circle(200, 200, 100);
        cir.setFill(Color.CORAL);
        root.getChildren().add(cir);
        Scene scene = new Scene(root, 400, 400);
        */

        GridPane grid = new GridPane();
        grid.setAlignment(Pos.CENTER);
        grid.setHgap(10);
        grid.setVgap(10);
        grid.setPadding(new Insets(25, 25, 25, 25));

        Scene scene = new Scene(grid, 300, 250);

        Text sceneTitle = new Text("Please Login: ");
        sceneTitle.setFont(Font.font("Tahoma", FontWeight.NORMAL, 20));
        Label userName = new Label("Username:");
        TextField userTextField = new TextField();
        Label passWord = new Label("Password:");
        PasswordField passTextField = new PasswordField();

        grid.add(sceneTitle, 0, 0, 2, 1);
        grid.add(userName, 0, 1, 1, 1);
        grid.add(userTextField, 1, 1, 1, 1);
        grid.add(passWord, 0, 2, 1, 1);
        grid.add(passTextField, 1, 2, 1, 1);


        grid.setGridLinesVisible(false);

        Button button = new Button("Sign in");
        HBox hbBtn = new HBox(10);
        hbBtn.setAlignment(Pos.BOTTOM_RIGHT);
        hbBtn.getChildren().add(button);

        grid.add(hbBtn, 1, 3);

        final Text actionTarget = new Text();
        grid.add(actionTarget, 1, 6);

        button.setOnAction(e -> {
            actionTarget.setFill(Color.FIREBRICK);
            actionTarget.setText("Action button pressed!");
        });


        primaryStage.setTitle("JavaFX Login Form");
        primaryStage.setScene(scene);
        primaryStage.show();

    }
}
