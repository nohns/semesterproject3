/** @format */

import { Button } from "@/components/ui/button";
import {
  AlertDialog,
  AlertDialogAction,
  AlertDialogCancel,
  AlertDialogContent,
  AlertDialogDescription,
  AlertDialogFooter,
  AlertDialogHeader,
  AlertDialogTitle,
  AlertDialogTrigger,
} from "@/components/ui/alert-dialog";
import { useEffect, useState } from "react";
import useGetContainers, {
  FluidContainer,
} from "@/api/endpoints/container/getContainers";

import { Progress } from "@/components/ui/progress";
import CustomAlertDialogAction from "@/components/CustomAlertDialogAction";

enum GuideState {
  step1 = 10,
  step2 = 25,
  step3 = 50,
  step4 = 75,
  step5 = 85,
  step6 = 100,
}

interface ChangeContainerGuideProps {
  container1: FluidContainer;
  container2: FluidContainer;
  container3: FluidContainer;
  handleChangeContainer: () => void;
}

function ChangeContainerGuide({
  container1,
  container2,
  container3,
  handleChangeContainer,
}: ChangeContainerGuideProps) {
  //I think we just need to pass in the current state of the fluid containers and use those as instructions for the guide
  //Then at the end we can call change container with the new containers

  const [step, setStep] = useState<GuideState>(GuideState.step1);

  const handleStep = () => {
    //Increment step to the next possible enum value
    const nextStep = (Object.values(GuideState) as GuideState[]).find(
      (stepValue: GuideState) => stepValue > step
    );

    if (nextStep) {
      setStep(nextStep);
    }
  };

  //Steps passer ikke rigtigt med hvad der skal ske
  const renderView = () => {
    switch (step) {
      case GuideState.step1:
        return <p>Place a cup under the outlet.</p>;
      case GuideState.step2:
        return <p>Lift the tubes out of the fluid in the container.</p>;
      case GuideState.step3:
        return (
          <p>
            Start the pump by flipping the switch on the machine and wait until
            the remaining liquid in the tube stops coming out.
          </p>
        );
      case GuideState.step4:
        return (
          <p>
            Stop the pump by flipping the switch back and empty the liquid in
            the containers manually
          </p>
        );

      case GuideState.step5:
        return (
          <div className="">
            <p className="mb-4">
              Fill the containers with the following liquid
            </p>

            <div className="border p-5 mt-4 flex gap-6 flex-col rounded-xl font-mono text-black text-lg">
              <p className="border-b">container1: {container1.fluid.name}</p>
              <p className="border-b">container2: {container2.fluid.name}</p>
              <p className="border-b">container3: {container3.fluid.name}</p>
            </div>
          </div>
        );
      case GuideState.step6:
        return (
          <p>The system is now configured with the new liquids and drinks</p>
        );
      default:
        return <p>Something went wrong :/</p>;
    }
  };

  const handleSubmit = () => {
    console.log("Submitting stuff");
    handleChangeContainer();
    setStep(GuideState.step1);
  };

  return (
    <>
      <AlertDialog>
        <AlertDialogTrigger className="py-10 px-16">
          Update menu
        </AlertDialogTrigger>
        <AlertDialogContent>
          <AlertDialogHeader>
            <AlertDialogTitle>Configuration guide</AlertDialogTitle>
            <AlertDialogDescription>{renderView()}</AlertDialogDescription>
          </AlertDialogHeader>
          <AlertDialogFooter>
            {step !== GuideState.step6 && (
              <Button onClick={handleStep}>Continue</Button>
            )}
            {step === GuideState.step6 && (
              <CustomAlertDialogAction onClose={() => handleSubmit()}>
                Finish
              </CustomAlertDialogAction>
            )}
          </AlertDialogFooter>
          <Progress value={step} />
        </AlertDialogContent>
      </AlertDialog>
    </>
  );
}

export default ChangeContainerGuide;

//1. Place the fluid containers under the outlet

//2. When done, press "OK"

//3. The system will now pump out the fluid from the containers

//4 The system will now show "Finished pumping out" and show what each container should contain of fluid

// 1. Systemet viser guide for, hvilke beholdere som skal udskiftes og afventer, at administrator har stillet beholder under udtaget

/* Systemet viser guide for, hvilke beholdere som skal udskiftes og afventer, at administrator har stillet beholder under udtaget 
  
  Administrator stiller beholdere under udtaget 
  
  administrator trykker ”okay” 
  
  Systemet pumper væsken ud af beholdere 
  
  Systemet viser ”færdig med udpumpning” og viser hvad hver beholder skal indeholde af væske 
  
  Systemet afventer administrator fylder væske i beholdere 
  
  Administrator fylder væske i beholdere 
  
  Systemet registrerer beholdernes beholdning og viser ”Sortiment korrekt ændret”  */
