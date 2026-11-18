  while (bthSerial.available() > 0){
    bthCommand = unpackMessage(bluetoothMessageLength, bthSerial);

    if (bthCommand.equals("dir")){
      robotAction = unpackMessage(bluetoothMessageLength, bthSerial);
      
      if (robotAction.equals("dev")){
        readSpeed = unpackMessage(bluetoothMessageLength, bthSerial);
        robotSpeed = readSpeed.toInt();
        avancer(robotSpeed);
        delay(50);
      }
      if (robotAction.equals("der")){
        readSpeed = unpackMessage(bluetoothMessageLength, bthSerial);
        robotSpeed = readSpeed.toInt();
        reculer(robotSpeed);
        delay(50);
      }
      if (robotAction.equals("gau")){
        readSpeed = unpackMessage(bluetoothMessageLength, bthSerial);
        robotSpeed = readSpeed.toInt();
        tourneragauche();
        delay(50);
      }
      if (robotAction.equals("dro")){
        readSpeed = unpackMessage(bluetoothMessageLength, bthSerial);
        robotSpeed = readSpeed.toInt();
        tourneradroite();
        delay(50);
      }
      if (robotAction.equals("sto")){
        readSpeed = unpackMessage(bluetoothMessageLength, bthSerial);
        robotSpeed = readSpeed.toInt();
        arreter();
        delay(50);
      }
    }
    if (bthCommand.equals("led")){
      robotAction = unpackMessage(bluetoothMessageLength, bthSerial);

      if (robotAction.equals("ton")){
        lights = "on";
      } else if (robotAction.equals("tof")){
        lights = "off";
      } else if (robotAction.equals("swt")){
        pattern = (pattern + 1) % 12;
      }
    }
    bthCommand = "";
    readSpeed = "";
    robotAction = "";
  }