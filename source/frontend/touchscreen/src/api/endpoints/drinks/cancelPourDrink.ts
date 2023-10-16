/** @format */

import ENV from "@/constants/env";

import { useMutation, useQueryClient } from "@tanstack/react-query";

import { http } from "@/api/axios";

if (ENV.MOCKED) {
  await import("./cancelPourDrink.mock.ts");
}

interface CancelPourDrinkRequest {
  id: number;
}

export interface CancelPourDrinkResponse {}

const cancelPourDrink = async (request: CancelPourDrinkRequest) => {
  return await http.post<CancelPourDrinkResponse>("v1/drinks/cancel", request);
};

const useCancelPourDrink = () => {
  const queryClient = useQueryClient();

  return useMutation({
    mutationFn: (request: CancelPourDrinkRequest) => {
      if (!request) {
        return Promise.resolve(null);
      }

      return cancelPourDrink(request);
    },
    mutationKey: ["pourDrink"],
    onSuccess: () => {
      queryClient.invalidateQueries(["getDrinks"]);
    },
  });
};

export default useCancelPourDrink;
