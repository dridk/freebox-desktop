import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.0

ScrollView {
    width: window.width
    height: window.height

    // Headers
    Rectangle {
        id:content
        width: 500
        height: subContent.height *2
        color: "transparent"
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20


        //---------HEADER -------------
        Column {
            width: parent.width
            Column {
                width: parent.width
                height: 100
                spacing: 50
                Row {
                    spacing: 40
                    Image  {
                        source: "qrc:///unknown.jpg"
                        width: 80
                        height: 80
                        fillMode: Image.PreserveAspectCrop

                    }
                    ColumnLayout {
                        Label {
                            text: "Mr.Keller Andre"
                            font.pixelSize: 24
                            font.bold: true

                        }
                        Label {
                            text: "Schutz Sacha"
                            font.pixelSize: 20

                        }
                        Label {
                            text: "stylite Gmbh"
                            font.pixelSize: 18
                            font.italic: true
                        }

                    }
                }
            } //--------- END HEADER -------------

            ColumnLayout {
                spacing: 20
                id:subContent

                //--------TELEPHONE ------
                CTDetailItem {
                    title: "Téléphone:"
                    content: ColumnLayout {
                        Repeater {
                            model:2
                            Label {
                                text: "[Maison] +33651571606"
                                font.pixelSize: 16

                              }

                        }
                    }
                }  //--- FIN TELEPHONE ------
                //--------EMAIL ------
                CTDetailItem {
                    title: "Email:"
                    content: ColumnLayout {
                        Repeater {
                            model:2
                            Text {
                                text: "sacha@labsquare.org"
                                font.pixelSize: 16
                            }

                        }
                    }
                }  //--- FIN EMAIL ------
                //--------ADRESSE ------
                CTDetailItem {
                    title: "Adresse:"
                    content: ColumnLayout {
                        Repeater {
                            model:2
                            Text {
                                text: "<a href='#'>33 Rue des roses<br/>14000 Caen<br/>France</a>"
                                font.pixelSize:16
                                wrapMode: Text.WordWrap
                                onLinkActivated: console.debug("hello")
                            }

                        }
                    }
                }  //--- FIN ADRESSE ------
                //--------URL ------
                CTDetailItem {
                    title: "URL:"
                    content: ColumnLayout {
                        Repeater {
                            model:2
                            Text {
                                text: "<a href='#'>http://www.labsquare.org</a>"
                                font.pixelSize:16
                            }

                        }
                    }
                }  //--- FIN URL ------
                //--------URL ------
                CTDetailItem {
                    title: "Note:"
                    content: Text {
                        text:"Le Lorem Ipsum est simplement du faux texte employé dans la composition et la mise en page avant impression. Le Lorem Ipsum est le faux texte standard de l'imprimerie depuis les années 1500, quand un peintre anonyme assembla ensemble des morceaux"
                        wrapMode: Text.WordWrap
                        width: 400
                        font.pixelSize:16

                    }
                }  //--- FIN URL ------
            }

        }
    }


}





