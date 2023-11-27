/** @format */

import React from "react";
import { AlertDialogAction } from "@/components/ui/alert-dialog";

interface CustomAlertDialogActionProps {
  onClose: () => void;
  children: React.ReactNode;
}

const CustomAlertDialogAction: React.FC<CustomAlertDialogActionProps> = ({
  onClose,
  children,
}) => {
  return <AlertDialogAction onClick={onClose}>{children}</AlertDialogAction>;
};

export default CustomAlertDialogAction;
