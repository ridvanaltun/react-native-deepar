export default {
  capitalize(s: String): String {
    if (typeof s !== 'string') {
      return '';
    }

    return s.charAt(0).toUpperCase() + s.slice(1);
  },
  randomNumber(min: number, max: number) {
    return Math.floor(Math.random() * (max - min + 1)) + min;
  },
};
