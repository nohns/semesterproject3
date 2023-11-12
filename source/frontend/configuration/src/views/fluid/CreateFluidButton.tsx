/** @format */

import { Button } from "@/components/ui/button";
import React from "react";

interface CreateFluidButtonProps {
  createFluid: () => void;
}

function CreateFluidButton({ createFluid }: CreateFluidButtonProps) {
  return (
    <>
      <div>
        <Button onClick={createFluid}>Create Fluid</Button>
      </div>
    </>
  );
}

export default CreateFluidButton;
