/** @format */

import { useState } from "react";
import {
  DropdownMenu,
  DropdownMenuTrigger,
  DropdownMenuContent,
  DropdownMenuRadioGroup,
  DropdownMenuRadioItem,
  DropdownMenuLabel,
  DropdownMenuSeparator,
} from "@/components/ui/dropdown-menu";

import { Button } from "@/components/ui/button";
import { Fluid } from "@/api/endpoints/fluid/getFluids";
import { FluidContainer } from "@/api/endpoints/container/getContainers";

interface CustomDropdownProps {
  container: FluidContainer;
  setContainer: React.Dispatch<React.SetStateAction<FluidContainer>>;
  fluids: Fluid[];
  className?: string;
}

function CustomDropdown({
  container,
  setContainer,
  fluids,
  className,
}: CustomDropdownProps) {
  return (
    <DropdownMenu>
      <DropdownMenuTrigger asChild className={className}>
        <Button className="text-black">{container.fluid.name}</Button>
      </DropdownMenuTrigger>
      <DropdownMenuContent>
        <DropdownMenuLabel>Drinks</DropdownMenuLabel>
        <DropdownMenuSeparator />
        <DropdownMenuRadioGroup
          value={container.fluid.name}
          onValueChange={(value) => {
            const selectedFluid = fluids.find((fluid) => fluid.name === value);
            if (selectedFluid) {
              setContainer({
                fluid: selectedFluid,
                fluidAmountInCl: 0,
                id: container.id,
              });
            }
          }}
        >
          {fluids.map((fluid) => (
            <DropdownMenuRadioItem key={fluid.name} value={fluid.name}>
              {fluid.name}
            </DropdownMenuRadioItem>
          ))}
        </DropdownMenuRadioGroup>
      </DropdownMenuContent>
    </DropdownMenu>
  );
}

export default CustomDropdown;
