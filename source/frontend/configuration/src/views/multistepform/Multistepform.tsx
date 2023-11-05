/** @format */

import { useState } from "react";

//https://www.npmjs.com/package/react-multistep

import Step1 from "./Step1";
import Step2 from "./Step2";
import Step3 from "./Step3";
import Step4 from "./Step4";
import Step5 from "./Step5";
import Step6 from "./Step6";
import Step7 from "./Step7";

function Multistepform(): JSX.Element {
  const [activeStep, setActiveStep] = useState(0);

  return (
    <>
      <div className=" flex flex-row justify-center"></div>
    </>
  );
}

export default Multistepform;
