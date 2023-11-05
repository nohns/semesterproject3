/** @format */

import ENV from "@/constants/env";

import { useQuery } from "@tanstack/react-query";

import { http } from "@/api/axios";

if (ENV.MOCKED) {
  await import("./getImages.mock.ts");
}

export interface Image {
  id: number;
  path: string;
}

interface GetImagesRequest {}

export interface GetImagesResponse {
  images: Image[];
}

const getImages = async ({}: GetImagesRequest) => {
  const response = await http.get<GetImagesResponse>(`v1/images`);

  if (response.status !== 200) {
    console.log(response);
    throw new Error("No data");
  }

  return response.data;
};

const useGetImages = () => {
  const query = useQuery({
    queryKey: ["getImages"],
    queryFn: () => getImages({}),
  });

  return query;
};

export default useGetImages;
